#ifndef DIRECTORY_H
#define DIRECTORY_H

#define DIRECTORY_NAME_MAX 64
#define DIRECTORY_PARENT_PATH_MAX 256

typedef struct {
    char name[DIRECTORY_NAME_MAX];
    char parent_path[DIRECTORY_PARENT_PATH_MAX];
} Directory;

void create_dir(char *args[100], char *cwd);
void delete_dir(char *args[100], char *cwd);
void rename_dir(char *args[100], char *cwd);

#endif
