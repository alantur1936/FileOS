#include "system.h"
#include "file.h"
#include "directory.h"
#include "utility.h"

// Validate the number of arguments after the command. (명령어 뒤 인자 개수 검사)
int check_args(
    const char *command,
    int argc,
    int min_args,
    int max_args
) {
    int argument_count = argc - 1;

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

// Split a line into command and arguments. (입력 한 줄을 명령어와 인자로 분리)
void process_command(char *user_input, char *cwd) {
    char *args[100];
    int arg_count = 0;

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

// Route a command to its feature function. (명령어에 맞는 기능 함수 호출)
void execute_command(int argc, char *args[100], char *cwd) {
    const char *command = args[0];

    if (strcmp(command, "create") == 0) {
        if (!check_args(command, argc, 1, 1)) return;
        create_file(args, cwd);
    }
    else if (strcmp(command, "delete") == 0) {
        if (!check_args(command, argc, 1, 1)) return;
        delete_file(args, cwd);
    }
    else if (strcmp(command, "write") == 0) {
        if (!check_args(command, argc, 1, 1)) return;
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
