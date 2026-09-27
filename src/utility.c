#include "utility.h"
#include "storage.h"
#include "color.h"

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
            printf(COLOR_DIRECTORY "%s\n" COLOR_RESET, directories[i].name);
            entry_count++;
        }
    }

    // Report an empty current directory. (현재 디렉터리가 비어 있음을 알림)
    if (entry_count == 0) {
        printf(COLOR_ERROR "ls: empty\n" COLOR_RESET);
    }
}

void cd_command(char *args[100], char *cwd)
{
    const char *target = args[1];

    // "~" returns to the home directory. ("~"는 홈 디렉터리로 이동)
    if (strcmp(target, "~") == 0) {
        snprintf(cwd, FILE_PATH_MAX, "%s", "/home");
        return;
    }

    // "/" moves to the root directory. ("/"는 루트 디렉터리로 이동)
    if (strcmp(target, "/") == 0) {
        snprintf(cwd, FILE_PATH_MAX, "%s", "/");
        return;
    }

    // ".." removes the last directory name. (".."은 마지막 디렉터리 이름 제거)
    if (strcmp(target, "..") == 0) {
        char *last_slash;

        if (strcmp(cwd, "/") == 0) {
            return;
        }

        last_slash = strrchr(cwd, '/');

        if (last_slash == cwd) {
            cwd[1] = '\0';
        } else {
            *last_slash = '\0';
        }

        return;
    }

    for (int i = 0; i < directory_count; i++) {
        if (strcmp(directories[i].parent_path, cwd) == 0 &&
            strcmp(directories[i].name, target) == 0) {
            char path[FILE_PATH_MAX];

            // Prevent a child path longer than the current-path buffer. (현재 경로 저장 공간보다 긴 하위 경로 방지)
            if (strcmp(cwd, "/") == 0) {
                if (snprintf(path, sizeof(path), "/%s", target) >= (int)sizeof(path)) {
                    printf(COLOR_ERROR "cd: path too long\n" COLOR_RESET);
                    return;
                }
            } else if (snprintf(path, sizeof(path), "%s/%s", cwd, target) >= (int)sizeof(path)) {
                printf(COLOR_ERROR "cd: path too long\n" COLOR_RESET);
                return;
            }

            snprintf(cwd, FILE_PATH_MAX, "%s", path);
            return;
        }
    }

    // Do not change paths when the target does not exist. (대상 디렉터리가 없으면 경로 변경 방지)
    printf(COLOR_ERROR "cd: directory not found\n" COLOR_RESET);
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
        printf(COLOR_ERROR "list: command guide not found\n" COLOR_RESET);
        return;
    }

    while ((c = fgetc(file)) != EOF)
        putchar(c);

    // Report a read failure separately from normal EOF. (정상 파일 끝과 읽기 오류 구분)
    if (ferror(file)) {
        printf(COLOR_ERROR "list: failed to read command guide\n" COLOR_RESET);
    }

    fclose(file);
}
