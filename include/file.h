#ifndef FILE_H
#define FILE_H

#define FILE_PATH_MAX 256
#define FILE_CONTENT_MAX 1024

typedef struct {
    char path[FILE_PATH_MAX];        // Virtual path (예: /home/memo.txt)
    char content[FILE_CONTENT_MAX];  // File contents (파일 내용)
} File;

void create_file(char *args[100], char *cwd); // Create file (파일 생성)
void delete_file(char *args[100], char *cwd); // Delete file (파일 삭제)
void write_file(char *args[100], char *cwd); // Write file (파일 쓰기)
void read_file(char *args[100], char *cwd); // Read file (파일 읽기)
void rename_file(char *args[100], char *cwd); // Rename file (파일 이름 수정)

#endif
