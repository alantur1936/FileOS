#ifndef DIRECTORY_H
#define DIRECTORY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Directory {
    char *name;
    struct Directory *parent;
} Directory;

void create_dir(char *args[100], char *cwd);
void delete_dir(char *args[100], char *cwd);
void write_dir(char *args[100], char *cwd);
void read_dir(char *args[100], char *cwd);
void rename_dir(char *args[100], char *cwd);

#endif
