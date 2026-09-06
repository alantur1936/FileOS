#include <stdio.h>
#include <string.h>
#include "third_party/cJSON-master/cJSON.h"

void process_command(char* user_input, char* cwd);
char* find_command(char* command);
