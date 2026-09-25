#include "utility.h"

void ls_command(char *args[100], char *cwd)
{
}

void cd_command(char *args[100], char *cwd)
{
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
