#include "../include/parser.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char *function_to_c(M_TNode *token_node, int T_KEYWORD) // if we find the function, traverse the function until the end and convert the function to c syntax
{
    if (token_node->token_data->token_type != T_KEYWORD)
    {
        fprintf(stderr, "ERROR: unidentified keyword : function");
        exit(EXIT_FAILURE);
    }
}

Program *parse_program(Lexer *lexed_tokens)
{
    Program *new_program = malloc(sizeof(Program));
    M_TNode *token_iterator = lexed_tokens->root;

    while (token_iterator != NULL)
    {
        const char *value = token_iterator->token_data->value;
        if (token_iterator->token_data->token_type == T_KEYWORD && strcmp(value, "function") == 0)
        {
            // TEST--------
            char *c_test = function_to_c(token_iterator, T_KEYWORD);
        }

        token_iterator = token_iterator->next;
    }

    // Implement parsing for the entire program
}

// TO BE IMPLEMENTED