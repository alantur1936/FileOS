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
    FILE *file = fopen("droc/command.json", "r");

    if (file == NULL) {
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    rewind(file);

    char *json = malloc(size + 1);

    if (json == NULL) {
        fclose(file);
        return NULL;
    }

    fread(json, 1, size, file);
    json[size] = '\0';
    fclose(file);

    cJSON *root = cJSON_Parse(json);
    free(json);

    if (root == NULL) {
        return NULL;
    }

    cJSON *commands = cJSON_GetObjectItem(root, "commands");
    int size_commands = cJSON_GetArraySize(commands);

    for (int i = 0; i < size_commands; i++) {
        cJSON *item = cJSON_GetArrayItem(commands, i);
        cJSON *name = cJSON_GetObjectItem(item, "name");
        cJSON *function = cJSON_GetObjectItem(item, "function");

        if (strcmp(command, name->valuestring) == 0) {
            char *result = malloc(strlen(function->valuestring) + 1);

            if (result == NULL) {
                cJSON_Delete(root);
                return NULL;
            }

            strcpy(result, function->valuestring);
            cJSON_Delete(root);
            return result;
        }
    }

    cJSON_Delete(root);
    printf("Not command\n");
    return NULL;
}
