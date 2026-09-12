#include "utility.h"

// List directory (디렉터리 목록 출력)
void ls_command(void)
{
}

// Change directory (디렉터리 이동)
void cd_command(void)
{
}

// Print working directory (현재 경로 출력)
void pwd_command(void)
{
}

// List command (명령어 목록 출력)
void list_command(void)
{
    FILE *file = fopen("droc/command.txt", "r");
    int c;

    while ((c = fgetc(file)) != EOF)
        putchar(c);

    fclose(file);
}
