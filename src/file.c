#include "file.h"
#include "storage.h"
#include <stdio.h>
#include <string.h>

// Create file (파일 생성)
void create_file(char *args[100], char *cwd)
{
    char name[FILE_NAME_MAX];
    int copy_number = 0;

    // Check file storage space (파일 저장 공간 확인)
    if (file_count >= MAX_FILES) {
        printf("file: no space\n");
        return;
    }

    // Find an unused file name in the current directory (현재 경로에서 사용되지 않는 이름 찾기)
    while (copy_number < MAX_FILES) {
        int exists = 0;

        if (copy_number == 0) {
            snprintf(name, sizeof(name), "%s", args[1]);
        } else {
            snprintf(name, sizeof(name), "%s(%d)", args[1], copy_number);
        }

        // Check whether the same path and name already exist (같은 경로와 이름의 파일 존재 여부 확인)
        for (int i = 0; i < file_count; i++) {
            if (strcmp(files[i].path, cwd) == 0 &&
                strcmp(files[i].name, name) == 0) {
                exists = 1;
                break;
            }
        }

        if (!exists) {
            break;
        }

        copy_number++;
    }

    if (copy_number == MAX_FILES) {
        printf("file: no space\n");
        return;
    }

    // Store file information (파일 정보 저장)
    File *file = &files[file_count];

    snprintf(file->name, sizeof(file->name), "%s", name);
    snprintf(file->path, sizeof(file->path), "%s", cwd);
    file->content[0] = '\0';

    file_count++;
    printf("file created: %s/%s\n", file->path, file->name);
}

// Delete file (파일 삭제)
void delete_file(char *args[100], char *cwd)
{
    if (file_count == 0) {
        printf("file: not found\n");
        return;
    }
}

// Write file (파일 쓰기)
void write_file(char *args[100], char *cwd)
{
    if (file_count == 0) {
        printf("file: not found\n");
        return;
    }
}

// Read file (파일 읽기)
void read_file(char *args[100], char *cwd)
{
    if (file_count == 0) {
        printf("file: not found\n");
        return;
    }
}

// Rename file (파일 이름 수정)
void rename_file(char *args[100], char *cwd)
{
    int target_index = -1;
    char name[FILE_NAME_MAX];
    int copy_number = 0;

    // Find the file to rename (이름을 바꿀 파일 찾기)
    for (int i = 0; i < file_count; i++) {
        if (strcmp(files[i].path, cwd) == 0 &&
            strcmp(files[i].name, args[1]) == 0) {
            target_index = i;
            break;
        }
    }

    if (target_index == -1) {
        printf("file: not found\n");
        return;
    }

    // Find an unused new name (사용되지 않는 새 이름 찾기)
    while (copy_number < MAX_FILES) {
        int exists = 0;

        if (copy_number == 0) {
            snprintf(name, sizeof(name), "%s", args[2]);
        } else {
            snprintf(name, sizeof(name), "%s(%d)", args[2], copy_number);
        }

        for (int i = 0; i < file_count; i++) {
            if (i != target_index &&
                strcmp(files[i].path, cwd) == 0 &&
                strcmp(files[i].name, name) == 0) {
                exists = 1;
                break;
            }
        }

        if (!exists) {
            break;
        }

        copy_number++;
    }

    snprintf(files[target_index].name,
             sizeof(files[target_index].name),
             "%s",
             name);

    printf("file renamed: %s\n", files[target_index].name);
}
