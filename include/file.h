#ifndef FILE_H
#define FILE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *name;
    char *content;
    char *path;
} File;

void create_file(char *args[100], char *cwd); // Create file (파일 생성)
void delete_file(char *args[100], char *cwd); // Delete file (파일 삭제)
void write_file(char *args[100], char *cwd); // Write file (파일 쓰기)
void read_file(char *args[100], char *cwd); // Read file (파일 읽기)
void rename_file(char *args[100], char *cwd); // Rename file (파일 이름 수정)

#endif
