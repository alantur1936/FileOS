#ifndef SYSTEM_H
#define SYSTEM_H

#include <stdio.h>
#include <string.h>

int check_args(const char *command, int argc, int min_args, int max_args); // Check arguments (인자 검사)
void process_command(char *user_input, char *cwd); // Process command (명령어 처리)
void execute_command(int argc, char *args[100], char *cwd); // Execute command (명령어 실행)

#endif
