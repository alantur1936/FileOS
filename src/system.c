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

}

// Find command (명령어 찾기)
void (*find_command(char* command))(void) {

    // 명령어 이름을 확인하고 해당 함수 반환
    if (strcmp(command, "create") == 0)
        return create_file;

    if (strcmp(command, "delete") == 0)
        return delete_file;

    if (strcmp(command, "write") == 0)
        return write_file;

    if (strcmp(command, "read") == 0)
        return read_file;

    if (strcmp(command, "rename") == 0)
        return rename_file;

    if (strcmp(command, "create_dir") == 0)
        return create_dir;

    if (strcmp(command, "delete_dir") == 0)
        return delete_dir;

    if (strcmp(command, "write_dir") == 0)
        return write_dir;

    if (strcmp(command, "read_dir") == 0)
        return read_dir;

    if (strcmp(command, "rename_dir") == 0)
        return rename_dir;

    if (strcmp(command, "ls") == 0)
        return ls_command;

    if (strcmp(command, "cd") == 0)
        return cd_command;

    if (strcmp(command, "pwd") == 0)
        return pwd_command;

    if (strcmp(command, "list") == 0)
        return list_command;

    // 명령어를 찾지 못함
    printf("Not command\n");
    return NULL;
}
