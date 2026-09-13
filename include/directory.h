#ifndef DIRECTORY_H
#define DIRECTORY_H

#define DIRECTORY_PATH_MAX 256

typedef struct {
    char path[DIRECTORY_PATH_MAX];  // Virtual path (예: /home/docs)
} Directory;

void create_dir(char *args[100], char *cwd); // Create directory (디렉터리 생성)
void delete_dir(char *args[100], char *cwd); // Delete directory (디렉터리 삭제)
void write_dir(char *args[100], char *cwd); // Write directory (디렉터리 쓰기)
void read_dir(char *args[100], char *cwd); // Read directory (디렉터리 읽기)
void rename_dir(char *args[100], char *cwd); // Rename directory (디렉터리 이름 수정)

#endif
