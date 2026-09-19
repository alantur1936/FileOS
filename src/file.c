#include "file.h"
#include "storage.h"
#include <stdio.h>
#include <string.h>

// Create file (파일 생성)
void create_file(char *args[100], char *cwd)
{
    char path[FILE_PATH_MAX];
    int length;

    if (file_count >= MAX_FILES) {
        printf("file: no space\n");
        return;
    }

    if (args[1] == NULL || args[1][0] == '\0' ||
        strpbrk(args[1], "/\\") != NULL) {
        printf("file: invalid name\n");
        return;
    }

    if (strcmp(cwd, "/") == 0) {
        length = snprintf(path, sizeof(path), "/%s", args[1]);
    } else {
        length = snprintf(path, sizeof(path), "%s/%s", cwd, args[1]);
    }

    if (length < 0 || length >= (int)sizeof(path)) {
        printf("file: name too long\n");
        return;
    }

    for (int i = 0; i < file_count; i++) {
        if (strcmp(files[i].path, path) == 0) {
            printf("file: already exists\n");
            return;
        }
    }

    snprintf(files[file_count].name,
             sizeof(files[file_count].name),
             "%s",
             args[1]);
    snprintf(files[file_count].path,
             sizeof(files[file_count].path),
             "%s",
             path);
    files[file_count].content[0] = '\0';
    file_count++;

    printf("file created: %s\n", path);
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
