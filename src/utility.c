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
    FILE *file = fopen("droc/command.txt", "r");
    int c;

    while ((c = fgetc(file)) != EOF)
        putchar(c);

    fclose(file);
}
