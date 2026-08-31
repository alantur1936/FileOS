#include "command.h"

int main(void)
{
    char* cwd = "/home/";
    char* user_input;
    printf("FileOS:/home>\n");
    printf("> Exit: enter x\n");
    printf("> Command List: enter list\n");
    printf("> Version: 1.00\n");
    while (true) {
        printf("FileOS:/home> ");
        scanf("%s", user_input);
        if (strcmp(user_input, 'x')) {
            printf("Exit FileOS?(y/n):");
            char exit;
            scanf("%c", exit);
            if (strcmp(exit, 'y')) {
                break;
            } else if(strcmp(exit, 'n')) {
                continue;
            } else {
                printf("Enter 'y' or 'n'\n");
                continue;
            }
    }
    return 0;
}