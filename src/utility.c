#include "utility.h"

// List directory (디렉터리 목록 출력)
void ls_command(char *args[100], char *cwd)
{
}

// Change directory (디렉터리 이동)
void cd_command(char *args[100], char *cwd)
{
}

// Print working directory (현재 경로 출력)
void pwd_command(char *cwd)
{
    printf("%s\n", cwd);
}

// List command (명령어 목록 출력)
void list_command()
{
    FILE *file = fopen("droc/command.txt", "r");
    int c;


    while ((c = fgetc(file)) != EOF)
        putchar(c);

    fclose(file);
}
