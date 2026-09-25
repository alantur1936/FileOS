#include "directory.h"
#include "storage.h"
#include <stdio.h>
#include <string.h>

static int find_directory(const char *cwd, const char *name, int skip_index)
{
    for (int i = 0; i < directory_count; i++) {
        if (i != skip_index &&
            strcmp(directories[i].parent_path, cwd) == 0 &&
            strcmp(directories[i].name, name) == 0) {
            return i;
        }
    }

    return -1;
}

static int make_numbered_directory_name(char *name, const char *base,
                                        const char *cwd, int skip_index)
{
    for (int number = 0; number < MAX_DIRECTORIES; number++) {
        if (number == 0) {
            snprintf(name, DIRECTORY_NAME_MAX, "%s", base);
        } else {
            snprintf(name, DIRECTORY_NAME_MAX, "%s(%d)", base, number);
        }

        if (find_directory(cwd, name, skip_index) == -1) {
            return 1;
        }
    }

    return 0;
}

void create_dir(char *args[100], char *cwd)
{
    if (directory_count >= MAX_DIRECTORIES) {
        printf("directory: no space\n");
        return;
    }
}

void delete_dir(char *args[100], char *cwd)
{
    if (directory_count == 0) {
        printf("directory: not found\n");
        return;
    }
}

void rename_dir(char *args[100], char *cwd)
{
    if (directory_count == 0) {
        printf("directory: not found\n");
        return;
    }
}
