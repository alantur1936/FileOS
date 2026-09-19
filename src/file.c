#include "file.h"
#include "storage.h"
#include <stdio.h>
#include <string.h>

// Create file (파일 생성)
void create_file(char *args[100], char *cwd)
{
    char name[FILE_NAME_MAX];
    char path[FILE_PATH_MAX];
    int copy_number = 0;

    if (file_count >= MAX_FILES) {
        printf("file: no space\n");
        return;
    }

    while (copy_number < MAX_FILES) {
        int exists = 0;

        if (copy_number == 0) {
            snprintf(name, sizeof(name), "%s", args[1]);
        } else {
            snprintf(name, sizeof(name), "%s(%d)", args[1], copy_number);
        }

        snprintf(path, sizeof(path), "%s/%s", cwd, name);

        for (int i = 0; i < file_count; i++) {
            if (strcmp(files[i].path, path) == 0) {
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

    File *file = &files[file_count];

    snprintf(file->name, sizeof(file->name), "%s", name);
    snprintf(file->path, sizeof(file->path), "%s", path);
    file->content[0] = '\0';

    file_count++;
    printf("file created: %s\n", file->path);
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
    if (file_count == 0) {
        printf("file: not found\n");
        return;
    }
}
