#include "system.h"
#include <string.h>

int main(void)
{
    char* cwd = "/home";      // Current directory (현재 경로)
    char user_input[100];      // User input (사용자 입력)

    printf("FileOS:/home>\n");
    printf("> Exit: enter x\n");
    printf("> Command List: enter list\n");
    printf("> Version: 1.00\n");

    while (1) {
        printf("FileOS:%s ", cwd);
        if (scanf("%99s", user_input) != 1) {
            printf("Input failed.\n");
            return 1;
        }

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
                continue;
            }
        }

        process_command(user_input, cwd);
    }

    return 0;
}
