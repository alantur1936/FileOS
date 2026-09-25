#ifndef FILE_H
#define FILE_H

#define FILE_NAME_MAX 64
#define FILE_PATH_MAX 256
#define FILE_CONTENT_MAX 1024

typedef struct {
    char name[FILE_NAME_MAX];       // File name (파일 이름)
    char path[FILE_PATH_MAX];       // Containing directory (파일이 있는 디렉터리)
    char content[FILE_CONTENT_MAX]; // Stored text (저장된 내용)
} File;

void create_file(char *args[100], char *cwd);
void delete_file(char *args[100], char *cwd);
void write_file(char *args[100], char *cwd);
void read_file(char *args[100], char *cwd);
void rename_file(char *args[100], char *cwd);

#endif
