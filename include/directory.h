#include <stdio.h>

typedef struct {
    char name[256];
    struct Directory *parent;
};
} Directory;

void create_directory(void);
void delete_directory(void);
void write_directory(void);
void read_directory(void);
void rename_directory(void);
