#include "utility.h"
#include "storage.h"

void ls_command(char *args[100], char *cwd)
{
    int entry_count = 0; // Number of displayed entries. (출력한 항목 개수)

    for (int i = 0; i < file_count; i++) {
        if (strcmp(files[i].path, cwd) == 0) {
            printf("%s\n", files[i].name);
            entry_count++;
        }
    }

    for (int i = 0; i < directory_count; i++) {
        if (strcmp(directories[i].parent_path, cwd) == 0) {
            printf("%s\n", directories[i].name);
            entry_count++;
        }
    }

    // Report an empty current directory. (현재 디렉터리가 비어 있음을 알림)
    if (entry_count == 0) {
        printf("ls: empty\n");
    }
}

void cd_command(char *args[100], char *cwd)
{
    for (int i = 0; i < directory_count; i++) {
        if (strcmp(directories[i].parent_path, cwd) == 0 &&
            strcmp(directories[i].name, args[1]) == 0) {
            return;
        }
    }

    // Do not change paths when the target does not exist. (대상 디렉터리가 없으면 경로 변경 방지)
    printf("cd: directory not found\n");
}

void pwd_command(char *cwd)
{
    printf("%s\n", cwd);
}

void list_command(void)
{
    // Print the command guide file. (명령어 안내 파일 출력)
    FILE *file = fopen("droc/command.txt", "r");
    int c;

    // Stop if the guide file cannot be opened. (안내 파일을 열 수 없으면 중단)
    if (file == NULL) {
        printf("list: command guide not found\n");
        return;
    }

    while ((c = fgetc(file)) != EOF)
        putchar(c);

    // Report a read failure separately from normal EOF. (정상 파일 끝과 읽기 오류 구분)
    if (ferror(file)) {
        printf("list: failed to read command guide\n");
    }

    fclose(file);
}
