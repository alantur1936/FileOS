#include "file.h"
#include "storage.h"
#include <stdio.h>

// Create file (파일 생성)
void create_file(char *args[100], char *cwd)
{
    if (file_count >= MAX_FILES) {
        printf("file: no space\n");
        return;
    }
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
