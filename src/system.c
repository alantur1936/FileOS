#include "system.h"
#include "file.h"
#include "directory.h"
#include "utility.h"
#include "cJSON.h"

// Process command (명령어 처리)
void process_command(char* user_input, char* cwd) {
    char *args[100];
    int arg_count = 0;

    args[arg_count] = strtok(user_input, " ");

    while (args[arg_count] != NULL) {
        arg_count++;
        args[arg_count] = strtok(NULL, " ");
    }
 
}

char* find_command(char* command) {
}
