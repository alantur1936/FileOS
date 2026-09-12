#include "system.h"
#include "file.h"
#include "directory.h"
#include "utility.h"

// Process command (명령어 처리)
void process_command(char* user_input, char* cwd) {
    char *args[100];
    int arg_count = 0;

    args[arg_count] = strtok(user_input, " ");

    while (args[arg_count] != NULL) {
        arg_count++;
        args[arg_count] = strtok(NULL, " ");
    }

    execute_command(args[0]);

}

// Find command (명령어 찾기)
void execute_command(const char *command) {
    if (strcmp(command, "create") == 0) {
        create_file();
    }
    else if (strcmp(command, "delete") == 0) {
        delete_file();
    }
    else if (strcmp(command, "write") == 0) {
        write_file();
    }
    else if (strcmp(command, "read") == 0) {
        read_file();
    }
    else if (strcmp(command, "rename") == 0) {
        rename_file();
    }
    else if (strcmp(command, "create_dir") == 0) {
        create_dir();
    }
    else if (strcmp(command, "delete_dir") == 0) {
        delete_dir();
    }
    else if (strcmp(command, "write_dir") == 0) {
        write_dir();
    }
    else if (strcmp(command, "read_dir") == 0) {
        read_dir();
    }
    else if (strcmp(command, "rename_dir") == 0) {
        rename_dir();
    }
    else if (strcmp(command, "ls") == 0) {
        ls_command();
    }
    else if (strcmp(command, "cd") == 0) {
        cd_command();
    }
    else if (strcmp(command, "pwd") == 0) {
        pwd_command();
    }
    else if (strcmp(command, "list") == 0) {
        list_command();
    }
    else {
        printf("Not command\n");
    }
}
