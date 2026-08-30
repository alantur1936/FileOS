#include <stdio.h>

typedef struct Directory {
    char *name;
    struct Directory *parent;
} Directory;

void create_directory(void);
void delete_directory(void);
void write_directory(void);
void read_directory(void);
void rename_directory(void);
