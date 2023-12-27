#ifndef LEXER_H
#define LEXER_H

typedef struct M_LexNode
{
    struct M_LexNode *next;
    char *value;
} M_LexNode;

M_LexNode *init_lexeme(char *value);
M_LexNode *lex(char *contents);
void free_lexemes(M_LexNode *root);

#endif