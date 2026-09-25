#ifndef SYSTEM_H
#define SYSTEM_H

#include <stdio.h>
#include <string.h>

// Check whether a command received the required arguments. (명령어 인자 개수 확인)
int check_args(const char *command, int argc, int min_args, int max_args);

// Split input and pass it to the command handler. (입력을 나눠 명령어 처리기로 전달)
void process_command(char *user_input, char *cwd);

// Select and run the matching command. (명령어에 맞는 함수 실행)
void execute_command(int argc, char *args[100], char *cwd);

#endif
