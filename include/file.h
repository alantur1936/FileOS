#ifndef FILE_H
#define FILE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *name;
    char *content;
} File;

void create_file(void);
void delete_file(void);
void write_file(void);
void read_file(void);
void rename_file(void);

#endif
