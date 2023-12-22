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

void display_lexed_tokens(Lexer *lexed_tokens)
{
    M_TNode *lexed_temp_node = lexed_tokens->root;
    size_t node_iterator = 0;

    while (lexed_temp_node != NULL)
    {
        printf("TOKEN %zu (token_value : %s\t\t\t|| token_type : %d ) \n", node_iterator + 1, lexed_temp_node->token_data->value, lexed_temp_node->token_data->token_type);
        lexed_temp_node = lexed_temp_node->next;
        node_iterator++;
    }
}

Lexer *lex_tokens(int token_count, M_TNode *root)
{
    Lexer *lexed_tokens = malloc(sizeof(Lexer));
    lexed_tokens->root = NULL;

    if (lexed_tokens == NULL)
    {
        fprintf(stderr, "ERROR: mallocating lexer failed");
        free(lexed_tokens);
        exit(EXIT_FAILURE);
    }

    M_TNode *current_node = root;
    M_TNode *lexed_tokens_tail = NULL; // To keep track of the last node in lexed_tokens

    while (current_node != NULL)
    {
        M_Token *current_token = current_node->token_data;

        M_TNode *new_lexed_node = malloc(sizeof(M_TNode));
        new_lexed_node->token_data = malloc(sizeof(M_Token));
        new_lexed_node->token_data->value = malloc(strlen(current_token->value) + 1);

        if (new_lexed_node->token_data == NULL || new_lexed_node->token_data->value == NULL)
        {
            fprintf(stderr, "ERROR: mallocating lexed_tokens or its value failed");
            free(new_lexed_node->token_data->value);
            free(new_lexed_node->token_data);
            free(new_lexed_node);
            exit(EXIT_FAILURE);
        }

        strcpy(new_lexed_node->token_data->value, current_token->value);

        // Assign token_type based on value
        if (strcmp(current_token->value, "function") == 0)
        {
            new_lexed_node->token_data->token_type = T_KEYWORD;
        }
        else if (is_number(current_token->value))
        {
            new_lexed_node->token_data->token_type = T_INTEGER_LITERAL;
        }
        else if (strcmp(current_token->value, "(") == 0)
        {
            new_lexed_node->token_data->token_type = T_LPAREN;
        }
        else if (strcmp(current_token->value, ":") == 0)
        {
            new_lexed_node->token_data->token_type = T_COLON;
        }
        else if (strcmp(current_token->value, ")") == 0)
        {
            new_lexed_node->token_data->token_type = T_RPAREN;
        }
        else if (strcmp(current_token->value, ",") == 0)
        {
            new_lexed_node->token_data->token_type = T_COMMA;
        }
        else if (strcmp(current_token->value, "int") == 0)
        {
            new_lexed_node->token_data->token_type = T_KEYWORD;
        }
        else if (strcmp(current_token->value, "char") == 0)
        {
            new_lexed_node->token_data->token_type = T_KEYWORD;
        }
        else if (strcmp(current_token->value, "int[]") == 0)
        {
            new_lexed_node->token_data->token_type = T_KEYWORD;
        }
        else if (strcmp(current_token->value, "return") == 0)
        {
            new_lexed_node->token_data->token_type = T_KEYWORD;
        }
        else if (strcmp(current_token->value, ";") == 0)
        {
            new_lexed_node->token_data->token_type = T_SEMI_COLON;
        }
        else if (strcmp(current_token->value, "{") == 0)
        {
            new_lexed_node->token_data->token_type = T_LCURL;
        }
        else if (strcmp(current_token->value, "}") == 0)
        {
            new_lexed_node->token_data->token_type = T_RCURL;
        }
        else
        {
            new_lexed_node->token_data->token_type = T_IDENTIFIER;
        }

        new_lexed_node->next = NULL;

        if (lexed_tokens->root == NULL)
        {
            lexed_tokens->root = new_lexed_node;
        }
        else
        {
            lexed_tokens_tail->next = new_lexed_node;
        }

        lexed_tokens_tail = new_lexed_node;
        current_node = current_node->next;
    }

    return lexed_tokens;
}