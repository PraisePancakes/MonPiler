#ifndef TOKENIZER_H
#define TOKENIZER_H
#include "lexer.h"

/*
    TOKENIZER WILL TAKE A LINKED LIST OF LEXEMES, ADD VALUE TO THOSE LEXEMES SUCH AS TOKEN TYPE, AND ULTIMATELY RETURN A LINKED LIST OF TOKENS, EXPECT THE LEXEMES LIST TO BE FREED RIGHT AFTER
*/

typedef struct M_Token
{
    int token_type;
    char *token_value;
} M_Token;

typedef struct M_TNode
{
    struct M_TNode *next;
    M_Token *data;
} M_TNode;

// populates the token types of each token node and returns the lexed_tokens
M_TNode *tokenize(M_LexNode *head);
void display_tokens(M_TNode *head);

#endif