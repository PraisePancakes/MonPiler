#include "../include/lexer.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

bool is_number(char *src)
{
    for (int i = 0; i < strlen(src); i++)
    {
        if (!isdigit(src[i]))
        {
            return false;
        }
    }
    return true;
}

Lexer *lex_tokens(int token_count, M_Token *token_array)
{
    Lexer *lexed_tokens = malloc(sizeof(Lexer));
    lexed_tokens->token_array = malloc(token_count * sizeof(M_Token));

    if (lexed_tokens->token_array == NULL || lexed_tokens == NULL)
    {
        fprintf(stderr, "ERROR: mallocating tokens failed");
        free(lexed_tokens->token_array);
        free(lexed_tokens);
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < token_count; i++)
    {
        lexed_tokens->token_array[i].value = malloc(strlen(token_array[i].value) + 1);

        if (lexed_tokens->token_array[i].value == NULL)
        {
            fprintf(stderr, "ERROR: mallocating lexed_tokens.value failed");
            free(lexed_tokens->token_array[i].value);
            exit(EXIT_FAILURE);
        }

        strcpy(lexed_tokens->token_array[i].value, token_array[i].value);

        if (strcmp(token_array[i].value, "function") == 0)
        {
            token_array[i].token_type = T_KEYWORD;
        }
        else if (is_number(token_array[i].value))
        {
            token_array[i].token_type = T_INTEGER_LITERAL;
        }
        else if (strcmp(token_array[i].value, "(") == 0)
        {
            token_array[i].token_type = T_LPAREN;
        }
        else if (strcmp(token_array[i].value, ":") == 0)
        {
            token_array[i].token_type = T_COLON;
        }
        else if (strcmp(token_array[i].value, ")") == 0)
        {
            token_array[i].token_type = T_RPAREN;
        }
        else if (strcmp(token_array[i].value, ",") == 0)
        {
            token_array[i].token_type = T_COMMA;
        }
        else if (strcmp(token_array[i].value, "int") == 0)
        {
            token_array[i].token_type = T_KEYWORD;
        }
        else if (strcmp(token_array[i].value, "char") == 0)
        {
            token_array[i].token_type = T_KEYWORD;
        }
        else if (strcmp(token_array[i].value, "int[]") == 0)
        {
            token_array[i].token_type = T_KEYWORD;
        }
        else if (strcmp(token_array[i].value, "return") == 0)
        {
            token_array[i].token_type = T_KEYWORD;
        }
        else if (strcmp(token_array[i].value, ";") == 0)
        {
            token_array[i].token_type = T_SEMI_COLON;
        }
        else if (strcmp(token_array[i].value, "{") == 0)
        {
            token_array[i].token_type = T_LCURL;
        }
        else if (strcmp(token_array[i].value, "}") == 0)
        {
            token_array[i].token_type = T_RCURL;
        }
        else
        {
            token_array[i].token_type = T_IDENTIFIER;
        }

        strcpy(lexed_tokens->token_array[i].value, token_array[i].value);
        lexed_tokens->token_array[i].token_type = token_array[i].token_type;
    }

    return lexed_tokens;
}