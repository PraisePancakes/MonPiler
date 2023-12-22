#ifndef LEXER_H
#define LEXER_H
#include "tokenizer.h"
#include <stdbool.h>
#include "file.h"

/*
    LEXER WILL TAKE AN ARRAY OF TOKENS, GO THROUGH EACH TOKEN AND ASSIGN A VALUE (TOKEN TYPE) TO THEM

*/

typedef struct Lexer
{
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

    M_TNode *root;
} Lexer;

// populates the token types of each token node and returns the lexed_tokens
Lexer *lex_tokens(int token_count, M_TNode *root);
void display_lexed_tokens(Lexer *lexed_tokens);
bool is_number(char *src);

#endif