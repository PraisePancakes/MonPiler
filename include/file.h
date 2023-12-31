#ifndef FILE_H
#define FILE_H
#include <stdio.h>

typedef struct M_File
{
    int word_count;
    char *contents;
    int length;
} M_File;

M_File *get_file(const char *const filepath);

#endif