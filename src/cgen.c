#include "../include/cgen.h"
#include <stdlib.h>
#include <stdio.h>

M_CFile *get_gcc_compatabile_file()
{
    FILE *fp = fopen("gen.c", "a");
    if (fp == NULL)
    {
        fprintf(stderr, "ERROR: failed to write to gcc compatible file");
        exit(EXIT_FAILURE);
    }

    M_CFile *c_file = malloc(sizeof(M_CFile));
    if (c_file == NULL)
    {
        fprintf(stderr, "ERROR: failed to mallocate gcc compatible generator file");
        exit(EXIT_FAILURE);
    }
    c_file->filtered_contents = NULL;

    return c_file;
}