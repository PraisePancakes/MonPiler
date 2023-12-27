#ifndef TOKENIZER_H
#define TOKENIZER_H
#include "lexer.h"
#include <stdbool.h>

/*
    LEXER WILL TAKE AN ARRAY OF TOKENS, GO THROUGH EACH TOKEN AND ASSIGN A VALUE (TOKEN TYPE) TO THEM

*/
/*
 const char *types[] = {
        "T_KEYWORD",
        "T_IDENTIFIER",
        "T_INTEGER_LITERAL",
        "T_STRING_LITERAL",
        "T_LPAREN",
        "T_RPAREN",
        "T_LBRACE",
        "T_RBRACE",
        "T_LCURL",
        "T_RCURL",
        "T_COLON",
        "T_COMMA",
        "T_SEMI_COLON",
    };

*/
typedef struct M_Token
{
    enum M_TOKEN_TYPE
    {
        T_AND,
        T_ARROW,
        T_BANG,
        T_BANG_EQUALS,
        T_CHAR,
        T_CHAR_ARRAY,
        T_COLON,
        T_COMMA,
        T_DOT,
        T_DOUBLE,
        T_DOUBLE_ARRAY,
        T_ELSE,
        T_EQUAL,
        T_EQUAL_EQUAL,
        T_FALSE,
        T_FLOAT,
        T_FLOAT_ARRAY,
        T_FOR,
        T_FUNCTION,
        T_GT,
        T_IDENTIFIER_LITERAL,
        T_IF,
        T_INT,
        T_INT_ARRAY,
        T_INTEGER_LITERAL,
        T_LBRACE,
        T_LCURL,
        T_LPAREN,
        T_LT,
        T_MINUS,
        T_NULL,
        T_OR,
        T_PLUS,
        T_PRINT,
        T_RETURN,
        T_RBRACE,
        T_RCURL,
        T_RPAREN,
        T_SEMI_COLON,
        T_SLASH,
        T_STAR,
        T_STRING_LITERAL,
        T_WHILE,
    } token_type;
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