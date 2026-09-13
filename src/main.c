#include "system.h"
#include <string.h>

int main(void)
{
    char cwd[256] = "/home";  // Current directory (현재 경로)
    char user_input[100];

    printf("FileOS:/home>\n");
    printf("> Exit: enter x\n");
    printf("> Command List: enter list\n");
    printf("> Version: 1.00\n");

    while (1) {
        printf("FileOS:%s ", cwd);

        if (fgets(user_input, sizeof(user_input), stdin) == NULL) {
            printf("Input failed.\n");
            return 1;
        }

        user_input[strcspn(user_input, "\n")] = '\0';

        if (user_input[0] == '\0') {
            continue;
        }

        if (strcmp(user_input, "x") == 0) {
            char exit_input[10];

            printf("Exit FileOS?(y/n): ");

            if (fgets(exit_input, sizeof(exit_input), stdin) == NULL) {
                printf("Input failed.\n");
                return 1;
            }

            if (exit_input[0] == 'y') {
                break;
            } else if (exit_input[0] == 'n') {
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
