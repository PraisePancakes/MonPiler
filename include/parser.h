#ifndef PARSER_H
#define PARSER_H
#include "lexer.h"

// TO BE IMPLEMENTED :: parse the linked list of tokens into c syntax, write the resulting syntax to a c file.

typedef struct Program
{
    char *parsed_src;
} Program;

Program *parse_program(Lexer *lexed_tokens);

#endif