#include "storage.h"

// Shared in-memory filesystem data. (프로그램이 함께 쓰는 가상 파일 시스템 데이터)
File files[MAX_FILES];
int file_count = 0;

Directory directories[MAX_DIRECTORIES];
int directory_count = 0;

void save_filesystem(void)
{
}

void load_filesystem(void)
{
}
