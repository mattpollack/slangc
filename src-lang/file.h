#ifndef _FILE_H
#define _FILE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct file_s {
    int     size;
    char    *buffer;
    char    *name;
}
file_t;

file_t file_load(char * file_name);
void   file_destroy(file_t * file);

#endif
