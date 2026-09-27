#include "system.h"
#include "storage.h"
#include "color.h"
#include <string.h>

int main(void)
{
    char cwd[256] = "/home"; // Maximum path length is 256. (경로 최대 길이는 256)
    char user_input[100];    // Maximum command length is 99 characters. (명령어 최대 길이는 99자)

    // Restore saved contents at startup. (시작 시 저장 내용 불러오기)
    load_filesystem();

    printf(COLOR_SUCCESS "FileOS:" COLOR_DIRECTORY "/home" COLOR_RESET " >\n");
    printf("> Exit: enter x\n");
    printf("> Command List: enter list\n");
    printf("> Version: 1.00\n");

    // Keep accepting commands until the user exits. (사용자가 종료할 때까지 명령어 입력)
    while (1) {
        printf(COLOR_SUCCESS "FileOS:" COLOR_DIRECTORY "%s" COLOR_RESET " > ", cwd);

        // Handle end-of-input or a read error. (입력 종료 또는 읽기 오류 처리)
        if (fgets(user_input, sizeof(user_input), stdin) == NULL) {
            printf(COLOR_ERROR "input: failed\n" COLOR_RESET);
            return 1;
        }

        // Remove the newline added by fgets. (fgets가 넣은 줄바꿈 제거)
        user_input[strcspn(user_input, "\n")] = '\0';

        if (user_input[0] == '\0') {
            continue;
        }

        if (strcmp(user_input, "x") == 0) {
            char exit_input[10]; // Enough for a short exit reply. (짧은 종료 응답용 공간)

            printf(COLOR_PROMPT "Exit FileOS? (y/n): " COLOR_RESET);

            // Handle end-of-input or a read error. (입력 종료 또는 읽기 오류 처리)
            if (fgets(exit_input, sizeof(exit_input), stdin) == NULL) {
                printf(COLOR_ERROR "input: failed\n" COLOR_RESET);
                return 1;
            }

            if (exit_input[0] == 'y') {
                break;
            } else if (exit_input[0] == 'n') {
                continue;
            } else {
                printf(COLOR_ERROR "exit: enter y or n\n" COLOR_RESET);
                continue;
            }
        }

        process_command(user_input, cwd);
    }

    return 0;
}
