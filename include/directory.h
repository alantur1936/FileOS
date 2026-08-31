#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Directory {
    char *name;
    struct Directory *parent;
} Directory;

void create_dir(void);
void delete_dir(void);
void write_dir(void);
void read_dir(void);
void rename_dir(void);
