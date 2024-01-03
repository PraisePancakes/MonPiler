#ifndef CGEN_H
#define CGEN_H
#include "parser.h"

typedef struct M_CFile
{
    char *filtered_contents;
} M_CFile;

M_CFile *get_gcc_compatabile_file();

#endif