#ifndef UTILITY_H
#define UTILITY_H

#include <stdio.h>
#include <string.h>

void ls_command(char *args[100], char *cwd); // List directory (디렉터리 목록 출력)
void cd_command(char *args[100], char *cwd); // Change directory (디렉터리 이동)
void pwd_command(char *cwd); // Print working directory (현재 경로 출력)
void list_command(); // List command (명령어 목록 출력)

#endif
