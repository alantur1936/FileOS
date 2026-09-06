#include "system.h"
#include "file.h"
#include "directory.h"
#include "utility.h"

// Process command (명령어 처리)
void process_command(char* user_input, char* cwd) {
    char *args[100];
    int arg_count = 0;

    args[arg_count] = strtok(user_input, " ");

    while (args[arg_count] != NULL) {
        arg_count++;
        args[arg_count] = strtok(NULL, " ");
    }

}

// Find command (명령어 찾기)
char* find_command(char* command) {

    // command.json 파일 열기
    FILE *file = fopen("droc/command.json", "r");

    if (file == NULL) {
        return NULL;
    }

    // 파일 크기 확인
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    rewind(file);

    // JSON 내용을 저장할 메모리 할당
    char *json = malloc(size + 1);

    if (json == NULL) {
        fclose(file);
        return NULL;
    }

    // 파일 내용 읽기
    fread(json, 1, size, file);
    json[size] = '\0';
    fclose(file);

    // JSON 파싱
    cJSON *root = cJSON_Parse(json);
    free(json);

    if (root == NULL) {
        return NULL;
    }

    // commands 배열 가져오기
    cJSON *commands = cJSON_GetObjectItem(root, "commands");
    int size_commands = cJSON_GetArraySize(commands);

    // 명령어 검색
    for (int i = 0; i < size_commands; i++) {

        // 현재 명령어 가져오기
        cJSON *item = cJSON_GetArrayItem(commands, i);
        cJSON *name = cJSON_GetObjectItem(item, "name");
        cJSON *function = cJSON_GetObjectItem(item, "function");

        // 명령어가 일치하는지 확인
        if (strcmp(command, name->valuestring) == 0) {

            // 함수 이름 저장
            char *result = malloc(strlen(function->valuestring) + 1);

            if (result == NULL) {
                cJSON_Delete(root);
                return NULL;
            }

            strcpy(result, function->valuestring);

            cJSON_Delete(root);

            // 함수 이름 반환
            return result;
        }
    }

    cJSON_Delete(root);

    // 명령어를 찾지 못함
    printf("Not command\n");

    return NULL;
}
