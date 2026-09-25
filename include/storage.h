#ifndef STORAGE_H
#define STORAGE_H

#include "file.h"
#include "directory.h"

#define MAX_FILES 100
#define MAX_DIRECTORIES 100

extern File files[MAX_FILES];
extern int file_count;

extern Directory directories[MAX_DIRECTORIES];
extern int directory_count;

void save_filesystem(void);
void load_filesystem(void);

#endif
