#ifndef SYSTEM_H
#define SYSTEM_H

#include <stdio.h>
#include <string.h>

int check_args(const char *command, int argc, int min_args, int max_args);
void process_command(char *user_input, char *cwd);
void execute_command(int argc, char *argv[], char *cwd);

#endif
