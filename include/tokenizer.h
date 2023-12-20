#ifndef TOKENIZER_H
#define TOKENIZER_H
#include "file.h"

typedef struct M_Token
{
    char *value;
    int token_type;
} M_Token;

M_Token *init_token(char *value);
int get_token_count(char *contents);
M_Token *tokenize(M_File *file, char *contents);

#endif