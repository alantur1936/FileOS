#ifndef STORAGE_H
#define STORAGE_H

#include "file.h"
#include "directory.h"

#define MAX_FILES 100
#define MAX_DIRECTORIES 100

extern File files[MAX_FILES];              // File storage (파일 저장 공간)
extern int file_count;                     // Number of stored files (저장된 파일 수)

extern Directory directories[MAX_DIRECTORIES]; // Directory storage (디렉터리 저장 공간)
extern int directory_count;                    // Number of stored directories (저장된 디렉터리 수)

void save_filesystem(void);
void load_filesystem(void);

#endif
