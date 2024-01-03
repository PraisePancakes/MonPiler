#include "../include/cgen.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

M_CFile *get_gcc_compatabile_file(char *filtered_contents)
{
    M_CFile *c_file = malloc(sizeof(M_CFile));
    if (c_file == NULL)
    {
        fprintf(stderr, "ERROR: failed to mallocate gcc compatible generator file");
        exit(EXIT_FAILURE);
    }

    c_file->filtered_contents = malloc(strlen(filtered_contents));
    strcpy(c_file->filtered_contents, filtered_contents);

    return c_file;
}

void write_to_gcc_compatible_file(M_CFile *compatible_file)
{
    FILE *fp = fopen("gen.c", "w");
    if (fp == NULL)
    {
        fprintf(stderr, "ERROR: generator compatible file unable to open");
        fclose(fp);
        exit(EXIT_FAILURE);
    }

    fputs(compatible_file->filtered_contents, fp);
    fclose(fp);
};