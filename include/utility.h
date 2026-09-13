#ifndef UTILITY_H
#define UTILITY_H

#include <stdio.h>
#include <string.h>

void ls_command(char *args[100], char *cwd);
void cd_command(char *args[100], char *cwd);
void pwd_command(char *args[100], char *cwd);
void list_command();

#endif
