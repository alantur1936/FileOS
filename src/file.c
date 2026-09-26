#include "file.h"
#include "storage.h"
#include "color.h"
#include <stdio.h>
#include <string.h>

// Find a file by its directory and name. (경로와 이름으로 파일 찾기)
static int find_file(const char *cwd, const char *name, int skip_index)
{
    for (int i = 0; i < file_count; i++) {
        if (i != skip_index &&
            strcmp(files[i].path, cwd) == 0 &&
            strcmp(files[i].name, name) == 0) {
            return i;
        }
    }

    return -1; // No matching file. (일치하는 파일 없음)
}

// Add (1), (2), ... when a name already exists. (이름이 겹치면 번호 붙이기)
static int make_numbered_name(char *name, const char *base,
                              const char *cwd, int skip_index)
{
    for (int number = 0; number < MAX_FILES; number++) {
        if (number == 0) { // Keep the original name first. (먼저 원래 이름 사용)
            snprintf(name, FILE_NAME_MAX, "%s", base);
        } else {
            snprintf(name, FILE_NAME_MAX, "%s(%d)", base, number);
        }

        if (find_file(cwd, name, skip_index) == -1) {
            return 1;
        }
    }

    return 0; // No available name remains. (사용 가능한 이름이 없음)
}

void create_file(char *args[100], char *cwd)
{
    char name[FILE_NAME_MAX];

    // Prevent writing past the file array. (파일 배열 범위 초과 방지)
    if (file_count >= MAX_FILES) {
        printf(COLOR_ERROR "file: no space\n" COLOR_RESET);
        return;
    }

    // Every numbered name is already in use. (번호를 붙인 모든 이름이 이미 사용 중)
    if (!make_numbered_name(name, args[1], cwd, -1)) {
        printf(COLOR_ERROR "file: no space\n" COLOR_RESET);
        return;
    }

    // Use the next empty storage slot. (다음 빈 저장 공간 사용)
    File *file = &files[file_count];

    snprintf(file->name, sizeof(file->name), "%s", name);
    snprintf(file->path, sizeof(file->path), "%s", cwd);
    file->content[0] = '\0';

    file_count++;
    printf(COLOR_SUCCESS "file created: %s/%s\n" COLOR_RESET, file->path, file->name);
}

void delete_file(char *args[100], char *cwd)
{
    int index = find_file(cwd, args[1], -1);

    // Stop before accessing an invalid array index. (잘못된 배열 인덱스 접근 방지)
    if (index == -1) {
        printf(COLOR_ERROR "file: not found\n" COLOR_RESET);
        return;
    }

    printf(COLOR_SUCCESS "file deleted: %s/%s\n" COLOR_RESET,
           files[index].path,
           files[index].name);

    // Shift later files into the removed slot. (뒤 파일을 앞으로 한 칸 이동)
    for (int i = index; i < file_count - 1; i++) {
        files[i] = files[i + 1];
    }

    file_count--;
}

void write_file(char *args[100], char *cwd)
{
    int index = find_file(cwd, args[1], -1);

    // Stop before accessing an invalid array index. (잘못된 배열 인덱스 접근 방지)
    if (index == -1) {
        printf(COLOR_ERROR "file: not found\n" COLOR_RESET);
        return;
    }

    File *file = &files[index];
    char content[FILE_CONTENT_MAX];

    printf(COLOR_PROMPT "Content: " COLOR_RESET);

    // Handle end-of-input or a read error. (입력 종료 또는 읽기 오류 처리)
    if (fgets(content, sizeof(content), stdin) == NULL) {
        printf(COLOR_ERROR "file: input failed\n" COLOR_RESET);
        return;
    }

    // A missing newline means the input may be too long. (줄바꿈이 없으면 입력 길이 확인)
    if (strchr(content, '\n') == NULL) {
        int ch = getchar();

        if (ch != '\n' && ch != EOF) {
            // Discard the rest of the long input. (남은 긴 입력 버리기)
            while ((ch = getchar()) != '\n' && ch != EOF) {
            }

            printf(COLOR_ERROR "file: content too long\n" COLOR_RESET);
            return;
        }
    }

    // Remove the newline before saving. (저장 전 줄바꿈 제거)
    content[strcspn(content, "\n")] = '\0';
    snprintf(file->content, sizeof(file->content), "%s", content);

    printf(COLOR_SUCCESS "file written: %s/%s\n" COLOR_RESET, file->path, file->name);
}

void read_file(char *args[100], char *cwd)
{
    int index = find_file(cwd, args[1], -1);

    // Stop before accessing an invalid array index. (잘못된 배열 인덱스 접근 방지)
    if (index == -1) {
        printf(COLOR_ERROR "file: not found\n" COLOR_RESET);
        return;
    }

    File *file = &files[index];
    printf("%s\n", file->content);
}

void rename_file(char *args[100], char *cwd)
{
    char name[FILE_NAME_MAX];
    int index = find_file(cwd, args[1], -1);

    // Stop before accessing an invalid array index. (잘못된 배열 인덱스 접근 방지)
    if (index == -1) {
        printf(COLOR_ERROR "file: not found\n" COLOR_RESET);
        return;
    }

    // Exclude this file while checking duplicate names. (자기 자신은 중복 검사에서 제외)
    if (!make_numbered_name(name, args[2], cwd, index)) {
        printf(COLOR_ERROR "file: no space\n" COLOR_RESET);
        return;
    }

    snprintf(files[index].name, sizeof(files[index].name), "%s", name);
    printf(COLOR_SUCCESS "file renamed: %s/%s\n" COLOR_RESET,
           files[index].path,
           files[index].name);
}
