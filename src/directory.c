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

// Join a parent path and directory name. (상위 경로와 디렉터리 이름 연결)
static int make_path(char *path, const char *parent_path, const char *name)
{
    return snprintf(path, DIRECTORY_PARENT_PATH_MAX, "%s/%s",
                    parent_path, name) < DIRECTORY_PARENT_PATH_MAX;
}

// Check whether a path is this directory or one of its children. (해당 디렉터리 또는 하위 경로인지 확인)
static int has_path_prefix(const char *path, const char *prefix)
{
    size_t length = strlen(prefix);

    return strncmp(path, prefix, length) == 0 &&
           (path[length] == '\0' || path[length] == '/');
}

// Replace the renamed directory prefix in a child path. (이름이 바뀐 디렉터리 경로로 하위 경로 갱신)
static int replace_path_prefix(char *path, const char *old_path,
                               const char *new_path)
{
    char updated_path[DIRECTORY_PARENT_PATH_MAX];
    const char *suffix = path + strlen(old_path);

    if (snprintf(updated_path, sizeof(updated_path), "%s%s",
                 new_path, suffix) >= (int)sizeof(updated_path)) {
        return 0;
    }

    snprintf(path, DIRECTORY_PARENT_PATH_MAX, "%s", updated_path);
    return 1;
}

void create_dir(char *args[100], char *cwd)
{
    char name[DIRECTORY_NAME_MAX];
    char path[DIRECTORY_PARENT_PATH_MAX];

    // Prevent writing past the directory array. (디렉터리 배열 범위 초과 방지)
    if (directory_count >= MAX_DIRECTORIES) {
        printf("directory: no space\n");
        return;
    }

    if (!make_numbered_directory_name(name, args[1], cwd, -1)) {
        printf("directory: no space\n");
        return;
    }

    // Prevent a directory path longer than the storage buffer. (저장 공간보다 긴 경로 방지)
    if (!make_path(path, cwd, name)) {
        printf("directory: path too long\n");
        return;
    }

    Directory *directory = &directories[directory_count];

    snprintf(directory->name, sizeof(directory->name), "%s", name);
    snprintf(directory->parent_path, sizeof(directory->parent_path), "%s", cwd);

    directory_count++;
    printf("directory created: %s\n", path);
}

void delete_dir(char *args[100], char *cwd)
{
    char path[DIRECTORY_PARENT_PATH_MAX];
    int index = find_directory(cwd, args[1], -1);

    // Stop before accessing an invalid array index. (잘못된 배열 인덱스 접근 방지)
    if (index == -1) {
        printf("directory: not found\n");
        return;
    }

    make_path(path, cwd, directories[index].name);

    // Keep directories that still contain files or child directories. (파일이나 하위 디렉터리가 있으면 삭제 방지)
    for (int i = 0; i < file_count; i++) {
        if (strcmp(files[i].path, path) == 0) {
            printf("directory: not empty\n");
            return;
        }
    }

    for (int i = 0; i < directory_count; i++) {
        if (strcmp(directories[i].parent_path, path) == 0) {
            printf("directory: not empty\n");
            return;
        }
    }

    printf("directory deleted: %s\n", path);

    // Shift later directories into the removed slot. (뒤 디렉터리를 앞으로 한 칸 이동)
    for (int i = index; i < directory_count - 1; i++) {
        directories[i] = directories[i + 1];
    }

    directory_count--;
}

void rename_dir(char *args[100], char *cwd)
{
    char name[DIRECTORY_NAME_MAX];
    char old_path[DIRECTORY_PARENT_PATH_MAX];
    char new_path[DIRECTORY_PARENT_PATH_MAX];
    int index = find_directory(cwd, args[1], -1);

    // Stop before accessing an invalid array index. (잘못된 배열 인덱스 접근 방지)
    if (index == -1) {
        printf("directory: not found\n");
        return;
    }

    // Exclude this directory while checking duplicate names. (자기 자신은 중복 검사에서 제외)
    if (!make_numbered_directory_name(name, args[2], cwd, index)) {
        printf("directory: no space\n");
        return;
    }

    make_path(old_path, cwd, directories[index].name);

    // Prevent a renamed path longer than the storage buffer. (이름 변경 후 경로 길이 초과 방지)
    if (!make_path(new_path, cwd, name)) {
        printf("directory: path too long\n");
        return;
    }

    // Check every child path before changing any stored data. (저장 데이터를 바꾸기 전에 모든 하위 경로 길이 확인)
    for (int i = 0; i < directory_count; i++) {
        if (has_path_prefix(directories[i].parent_path, old_path)) {
            char path[DIRECTORY_PARENT_PATH_MAX];

            snprintf(path, sizeof(path), "%s", directories[i].parent_path);
            if (!replace_path_prefix(path, old_path, new_path)) {
                printf("directory: path too long\n");
                return;
            }
        }
    }

    for (int i = 0; i < file_count; i++) {
        if (has_path_prefix(files[i].path, old_path)) {
            char path[FILE_PATH_MAX];

            snprintf(path, sizeof(path), "%s", files[i].path);
            if (!replace_path_prefix(path, old_path, new_path)) {
                printf("directory: path too long\n");
                return;
            }
        }
    }

    snprintf(directories[index].name, sizeof(directories[index].name), "%s", name);

    // Update paths of all files and directories inside it. (내부 파일·디렉터리 경로 모두 갱신)
    for (int i = 0; i < directory_count; i++) {
        if (has_path_prefix(directories[i].parent_path, old_path)) {
            replace_path_prefix(directories[i].parent_path, old_path, new_path);
        }
    }

    for (int i = 0; i < file_count; i++) {
        if (has_path_prefix(files[i].path, old_path)) {
            replace_path_prefix(files[i].path, old_path, new_path);
        }
    }

    printf("directory renamed: %s\n", new_path);
}
