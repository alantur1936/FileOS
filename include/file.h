#ifndef FILE_H
#define FILE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *name;
    char *content;
} File;

void create_file(char *args[100], char *cwd);
void delete_file(char *args[100], char *cwd);
void write_file(char *args[100], char *cwd);
void read_file(char *args[100], char *cwd);
void rename_file(char *args[100], char *cwd);

#endif
