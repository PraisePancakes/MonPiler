#ifndef FILE_H
#define FILE_H
#include <stdio.h>

typedef struct M_File
{
    int word_count;
    char *contents;
    int length;
} M_File;

int get_file_length(FILE *fp);
char *get_file_contents(FILE *fp, int file_length);
M_File *get_file(const char *const filepath);
int get_file_word_count(M_File *file);
int get_file_token_count(M_File *file);

#endif