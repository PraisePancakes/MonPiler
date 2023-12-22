#ifndef TOKENIZER_H
#define TOKENIZER_H
#include "file.h"

typedef struct M_Token
{
    char *value;
    int token_type;
} M_Token;

typedef struct M_TNode
{
    struct M_TNode *next;
    M_Token *token_data;
} M_TNode;

M_Token *init_token(char *value);
M_TNode *tokenize(int token_count, char *contents);
void free_tokens(M_TNode *root);

#endif