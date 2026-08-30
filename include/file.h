#include <stdio.h>

typedef struct {
    char name[256];
    char content[4096];
} File;

void create_file(void);
void delete_file(void);
void write_file(void);
void read_file(void);
void rename_file(void);
