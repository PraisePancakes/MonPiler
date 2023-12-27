#ifndef TOKENIZER_H
#define TOKENIZER_H
#include "lexer.h"
#include <stdbool.h>

/*
    LEXER WILL TAKE AN ARRAY OF TOKENS, GO THROUGH EACH TOKEN AND ASSIGN A VALUE (TOKEN TYPE) TO THEM

*/
enum M_TOKEN_TYPE
{
    T_KEYWORD,
    T_IDENTIFIER,
    T_INTEGER_LITERAL,
    T_LPAREN,
    T_RPAREN,
    T_LBRACE,
    T_RBRACE,
    T_LCURL,
    T_RCURL,
    T_COLON,
    T_COMMA,
    T_SEMI_COLON,
} M_TOKEN_TYPE;

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
bool is_number(char *src);

#endif