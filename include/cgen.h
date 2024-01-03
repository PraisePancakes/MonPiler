#ifndef CGEN_H
#define CGEN_H
#include "parser.h"

typedef struct M_CFile
{
    char *filtered_contents;
} M_CFile;

M_CFile *get_gcc_compatabile_file(char *filtered_contents);
void write_to_gcc_compatible_file(M_CFile *compatible_file);

#endif