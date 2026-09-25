#include "file.h"
#include "storage.h"
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

    return -1;
}

// Add (1), (2), ... when a name already exists. (이름이 겹치면 번호 붙이기)
static int make_numbered_name(char *name, const char *base,
                              const char *cwd, int skip_index)
{
    for (int number = 0; number < MAX_FILES; number++) {
        if (number == 0) {
            snprintf(name, FILE_NAME_MAX, "%s", base);
        } else {
            snprintf(name, FILE_NAME_MAX, "%s(%d)", base, number);
        }

        if (find_file(cwd, name, skip_index) == -1) {
            return 1;
        }
    }

    return 0;
}

void create_file(char *args[100], char *cwd)
{
    char name[FILE_NAME_MAX];

    if (file_count >= MAX_FILES) {
        printf("file: no space\n");
        return;
    }

    if (!make_numbered_name(name, args[1], cwd, -1)) {
        printf("file: no space\n");
        return;
    }

    // Use the next empty storage slot. (다음 빈 저장 공간 사용)
    File *file = &files[file_count];

    snprintf(file->name, sizeof(file->name), "%s", name);
    snprintf(file->path, sizeof(file->path), "%s", cwd);
    file->content[0] = '\0';

    file_count++;
    printf("file created: %s/%s\n", file->path, file->name);
}

void delete_file(char *args[100], char *cwd)
{
    int index = find_file(cwd, args[1], -1);

    if (index == -1) {
        printf("file: not found\n");
        return;
    }

    printf("file deleted: %s/%s\n",
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

    if (index == -1) {
        printf("file: not found\n");
        return;
    }

    File *file = &files[index];
    char content[FILE_CONTENT_MAX];

    printf("Content: ");

    if (fgets(content, sizeof(content), stdin) == NULL) {
        printf("file: input failed\n");
        return;
    }

    // A missing newline means the input may be too long. (줄바꿈이 없으면 입력 길이 확인)
    if (strchr(content, '\n') == NULL) {
        int ch = getchar();

        if (ch != '\n' && ch != EOF) {
            // Discard the rest of the long input. (남은 긴 입력 버리기)
            while ((ch = getchar()) != '\n' && ch != EOF) {
            }

            printf("file: content too long\n");
            return;
        }
    }

    // Remove the newline before saving. (저장 전 줄바꿈 제거)
    content[strcspn(content, "\n")] = '\0';
    snprintf(file->content, sizeof(file->content), "%s", content);

    printf("file written: %s/%s\n", file->path, file->name);
}

void read_file(char *args[100], char *cwd)
{
    int index = find_file(cwd, args[1], -1);

    if (index == -1) {
        printf("file: not found\n");
        return;
    }

    File *file = &files[index];
    printf("%s\n", file->content);
}

void rename_file(char *args[100], char *cwd)
{
    char name[FILE_NAME_MAX];
    int index = find_file(cwd, args[1], -1);

    if (index == -1) {
        printf("file: not found\n");
        return;
    }

    // Exclude this file while checking duplicate names. (자기 자신은 중복 검사에서 제외)
    if (!make_numbered_name(name, args[2], cwd, index)) {
        printf("file: no space\n");
        return;
    }

    snprintf(files[index].name, sizeof(files[index].name), "%s", name);
    printf("file renamed: %s/%s\n",
           files[index].path,
           files[index].name);
}
