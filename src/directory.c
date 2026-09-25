#include "directory.h"
#include "storage.h"
#include <stdio.h>
#include <string.h>

// Find a directory (디렉터리 찾기)
static int find_directory(const char *cwd, const char *name, int skip_index)
{
    // Compare the parent path and name of every stored directory (저장된 모든 디렉터리의 상위 경로와 이름 비교)
    for (int i = 0; i < directory_count; i++) {
        if (i != skip_index &&
            strcmp(directories[i].parent_path, cwd) == 0 &&
            strcmp(directories[i].name, name) == 0) {
            return i;
        }
    }

    // Return -1 when the directory does not exist (디렉터리가 없으면 -1 반환)
    return -1;
}

// Add a number to duplicate directory names (중복 디렉터리 이름에 번호 붙이기)
static int make_numbered_directory_name(char *name, const char *base,
                                        const char *cwd, int skip_index)
{
    // Try the original name, then (1), (2), and so on (원래 이름부터 번호를 붙여 확인)
    for (int number = 0; number < MAX_DIRECTORIES; number++) {
        if (number == 0) {
            snprintf(name, DIRECTORY_NAME_MAX, "%s", base);
        } else {
            snprintf(name, DIRECTORY_NAME_MAX, "%s(%d)", base, number);
        }

        // Finish when the name is not duplicated (중복되지 않는 이름이면 종료)
        if (find_directory(cwd, name, skip_index) == -1) {
            return 1;
        }
    }

    return 0;
}

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
