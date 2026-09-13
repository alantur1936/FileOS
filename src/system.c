#include "system.h"
#include "file.h"
#include "directory.h"
#include "utility.h"

// Check arguments (인자 검사)
int check_args(
    const char *command,
    int argc,
    int min_args,
    int max_args
) {
    int argument_count = argc - 1;  // Exclude command name (명령어 제외)

    if (argument_count < min_args) {
        printf("%s: too few arguments (min: %d)\n",
               command, min_args);
        return 0;
    }

    if (max_args != -1 && argument_count > max_args) {
        printf("%s: too many arguments (max: %d)\n",
               command, max_args);
        return 0;
    }

    return 1;
}

// Process command (명령어 처리)
void process_command(char *user_input, char *cwd) {
    char *args[100];  // Command tokens (명령어 토큰)
    int arg_count = 0;  // Token count (토큰 개수)

    args[arg_count] = strtok(user_input, " ");

    while (args[arg_count] != NULL && arg_count < 99) {
        arg_count++;
        args[arg_count] = strtok(NULL, " ");
    }

    if (arg_count == 0) {
        return;
    }

    execute_command(arg_count, args, cwd);
}

// Execute command (명령어 실행)
void execute_command(int argc, char *args[100], char *cwd) {
    const char *command = args[0];  // Command name (명령어 이름)

    if (strcmp(command, "create") == 0) {
        if (!check_args(command, argc, 1, 1)) return;
        create_file(args, cwd);
    }
    else if (strcmp(command, "delete") == 0) {
        if (!check_args(command, argc, 1, 1)) return;
        delete_file(args, cwd);
    }
    else if (strcmp(command, "write") == 0) {
        if (!check_args(command, argc, 2, 2)) return;
        write_file(args, cwd);
    }
    else if (strcmp(command, "read") == 0) {
        if (!check_args(command, argc, 1, 1)) return;
        read_file(args, cwd);
    }
    else if (strcmp(command, "rename") == 0) {
        if (!check_args(command, argc, 2, 2)) return;
        rename_file(args, cwd);
    }
    else if (strcmp(command, "create_dir") == 0) {
        if (!check_args(command, argc, 1, 1)) return;
        create_dir(args, cwd);
    }
    else if (strcmp(command, "delete_dir") == 0) {
        if (!check_args(command, argc, 1, 1)) return;
        delete_dir(args, cwd);
    }
    else if (strcmp(command, "write_dir") == 0) {
        if (!check_args(command, argc, 2, 2)) return;
        write_dir(args, cwd);
    }
    else if (strcmp(command, "read_dir") == 0) {
        if (!check_args(command, argc, 1, 1)) return;
        read_dir(args, cwd);
    }
    else if (strcmp(command, "rename_dir") == 0) {
        if (!check_args(command, argc, 2, 2)) return;
        rename_dir(args, cwd);
    }
    else if (strcmp(command, "ls") == 0) {
        if (!check_args(command, argc, 0, -1)) return;
        ls_command(args, cwd);
    }
    else if (strcmp(command, "cd") == 0) {
        if (!check_args(command, argc, 1, 1)) return;
        cd_command(args, cwd);
    }
    else if (strcmp(command, "pwd") == 0) {
        if (!check_args(command, argc, 0, 0)) return;
        pwd_command(cwd);
    }
    else if (strcmp(command, "list") == 0) {
        if (!check_args(command, argc, 0, 0)) return;
        list_command();
    }
    else {
        printf("%s: command not found\n", command);
    }
}
