#include "file.h"
#include "storage.h"
#include <stdio.h>
#include <string.h>

// Find a file in a directory (디렉터리에서 파일 찾기)
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

// Add a number to duplicate file names (중복 파일 이름에 번호 붙이기)
static int make_numbered_name(char *name, const char *base, const char *cwd, int skip_index)
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

// Create file (파일 생성)
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
    int index = find_file(cwd, args[1], -1);

    if (index == -1) {
        printf("file: not found\n");
        return;
    }

    for (int i = index; i < file_count - 1; i++) {
        files[i] = files[i + 1];
    }

    file_count--;

    printf("file deleted: %s\n", args[1]);
}

// Write file (파일 쓰기)
void write_file(char *args[100], char *cwd)
{
    int index = find_file(cwd, args[1], -1);

    if (index == -1) {
        printf("file: not found\n");
        return;
    }
    
    printf("file written: %s/%s\n", files[index].path, files[index].name);
    fgets(user_input, sizeof(user_input), stdin);
    
}

// Read file (파일 읽기)
void read_file(char *args[100], char *cwd)
{
    if (find_file(cwd, args[1], -1) == -1) {
        printf("file: not found\n");
        return;
    }
}

// Rename file (파일 이름 수정)
void rename_file(char *args[100], char *cwd)
{
    char name[FILE_NAME_MAX];
    int index = find_file(cwd, args[1], -1);

    if (index == -1) {
        printf("file: not found\n");
        return;
    }

    if (!make_numbered_name(name, args[2], cwd, index)) {
        printf("file: no space\n");
        return;
    }

    snprintf(files[index].name, sizeof(files[index].name), "%s", name);
    printf("file renamed: %s\n", files[index].name);
}
