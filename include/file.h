#ifndef FILE_H
#define FILE_H

#define FILE_NAME_MAX 64
#define FILE_PATH_MAX 256
#define FILE_CONTENT_MAX 1024

typedef struct {
    char name[FILE_NAME_MAX];
    char path[FILE_PATH_MAX];
    char content[FILE_CONTENT_MAX];
} File;

void create_file(char *args[100], char *cwd);
void delete_file(char *args[100], char *cwd);
void write_file(char *args[100], char *cwd);
void read_file(char *args[100], char *cwd);
void rename_file(char *args[100], char *cwd);

#endif
