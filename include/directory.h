#ifndef DIRECTORY_H
#define DIRECTORY_H

#define DIRECTORY_NAME_MAX 64
#define DIRECTORY_PARENT_PATH_MAX 256

typedef struct {
    char name[DIRECTORY_NAME_MAX];
    char parent_path[DIRECTORY_PARENT_PATH_MAX];
} Directory;

void create_dir(char *args[100], char *cwd); // Create directory (디렉터리 생성)
void delete_dir(char *args[100], char *cwd); // Delete directory (디렉터리 삭제)
void write_dir(char *args[100], char *cwd); // Write directory (디렉터리 쓰기)
void read_dir(char *args[100], char *cwd); // Read directory (디렉터리 읽기)
void rename_dir(char *args[100], char *cwd); // Rename directory (디렉터리 이름 수정)

#endif
