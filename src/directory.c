#include "directory.h"
#include "storage.h"
#include <stdio.h>
#include <string.h>

// Find a directory by its parent path and name. (상위 경로와 이름으로 디렉터리 찾기)
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
    char name[DIRECTORY_NAME_MAX];

    // Prevent writing past the directory array. (디렉터리 배열 범위 초과 방지)
    if (directory_count >= MAX_DIRECTORIES) {
        printf("directory: no space\n");
        return;
    }

    // Every numbered name is already in use. (번호를 붙인 모든 이름이 이미 사용 중)
    if (!make_numbered_directory_name(name, args[1], cwd, -1)) {
        printf("directory: no space\n");
        return;
    }

    // Use the next empty storage slot. (다음 빈 저장 공간 사용)
    Directory *directory = &directories[directory_count];

    snprintf(directory->name, sizeof(directory->name), "%s", name);
    snprintf(directory->parent_path, sizeof(directory->parent_path), "%s", cwd);

    directory_count++;
    printf("directory created: %s/%s\n",
           directory->parent_path,
           directory->name);
}

void delete_dir(char *args[100], char *cwd)
{
    int index = find_directory(cwd, args[1], -1);

    // Stop before accessing an invalid array index. (잘못된 배열 인덱스 접근 방지)
    if (index == -1) {
        printf("directory: not found\n");
        return;
    }

    printf("directory deleted: %s/%s\n",
           directories[index].parent_path,
           directories[index].name);

    // Shift later directories into the removed slot. (뒤 디렉터리를 앞으로 한 칸 이동)
    for (int i = index; i < directory_count - 1; i++) {
        directories[i] = directories[i + 1];
    }

    directory_count--;
}

void rename_dir(char *args[100], char *cwd)
{
    char name[DIRECTORY_NAME_MAX];
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

    snprintf(directories[index].name, sizeof(directories[index].name), "%s", name);
    printf("directory renamed: %s/%s\n",
           directories[index].parent_path,
           directories[index].name);
}
