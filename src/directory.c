#include "directory.h"
#include "storage.h"
#include <stdio.h>

// Create directory (디렉터리 생성)
void create_dir(char *args[100], char *cwd)
{
    if (directory_count >= MAX_DIRECTORIES) {
        printf("directory: no space\n");
        return;
    }
}

// Delete directory (디렉터리 삭제)
void delete_dir(char *args[100], char *cwd)
{
    if (directory_count == 0) {
        printf("directory: not found\n");
        return;
    }
}

// Rename directory (디렉터리 이름 수정)
void rename_dir(char *args[100], char *cwd)
{
    if (directory_count == 0) {
        printf("directory: not found\n");
        return;
    }
}
