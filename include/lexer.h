#ifndef LEXER_H
#define LEXER_H
#include "tokenizer.h"

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
    };

    M_Token *token_array;
    int token_count;

} Lexer;


#endif