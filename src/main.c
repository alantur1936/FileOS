#include "command.h"
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
    char* cwd = "/home/";
    char* user_input = malloc(100);

    printf("FileOS:/home>\n");
    printf("> Exit: enter x\n");
    printf("> Command List: enter list\n");
    printf("> Version: 1.00\n");

    while (true) {
        printf("FileOS:/home> ");
        scanf("%99s", user_input);

        if (strcmp(user_input, "x") == 0) {
            printf("Exit FileOS?(y/n): ");

            char exit;
            scanf(" %c", &exit);

            if (exit == 'y') {
                break;
            } else if (exit == 'n') {
                continue;
            } else {
                printf("Enter 'y' or 'n'\n");
            }
        }
    }

    free(user_input);

    return 0;
}