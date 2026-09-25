#include "directory.h"
#include "storage.h"
#include <stdio.h>
#include <string.h>

// Find a directory at the current path. (현재 경로에서 디렉터리 찾기)
static int find_directory(const char *cwd, const char *name, int skip_index)
{
    for (int i = 0; i < directory_count; i++) {
        if (i != skip_index &&
            strcmp(directories[i].parent_path, cwd) == 0 &&
            strcmp(directories[i].name, name) == 0) {
            return i;
        }
    }

    return -1; // No matching directory. (일치하는 디렉터리 없음)
}

// Add (1), (2), ... when a name already exists. (이름이 겹치면 번호 붙이기)
static int make_numbered_directory_name(char *name, const char *base,
                                        const char *cwd, int skip_index)
{
    for (int number = 0; number < MAX_DIRECTORIES; number++) {
        if (number == 0) { // Keep the original name first. (먼저 원래 이름 사용)
            snprintf(name, DIRECTORY_NAME_MAX, "%s", base);
        } else {
            snprintf(name, DIRECTORY_NAME_MAX, "%s(%d)", base, number);
        }

        if (find_directory(cwd, name, skip_index) == -1) {
            return 1;
        }
    }

    return 0; // No available name remains. (사용 가능한 이름이 없음)
}

void create_dir(char *args[100], char *cwd)
{
    // Prevent writing past the directory array. (디렉터리 배열 범위 초과 방지)
    if (directory_count >= MAX_DIRECTORIES) {
        printf("directory: no space\n");
        return;
    }
}

void delete_dir(char *args[100], char *cwd)
{
    // An empty list cannot contain the requested directory. (빈 목록에는 찾을 디렉터리가 없음)
    if (directory_count == 0) {
        printf("directory: not found\n");
        return;
    }
}

void rename_dir(char *args[100], char *cwd)
{
    // An empty list cannot contain the requested directory. (빈 목록에는 찾을 디렉터리가 없음)
    if (directory_count == 0) {
        printf("directory: not found\n");
        return;
    }
}
