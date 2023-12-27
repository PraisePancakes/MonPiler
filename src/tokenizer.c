
#include "../include/tokenizer.h"
#include "../include/lexer.h"
#include <stdlib.h>
#include <stdio.h>
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

void display_tokens(M_TNode *head)
{
    M_TNode *temp = head;
    size_t node_iterator = 0;

    while (temp != NULL)
    {
        printf("TOKEN %zu (token_value : %s\t\t\t|| token_type : %d ) \n", node_iterator + 1, temp->data->token_value, temp->data->token_type);
        temp = temp->next;
        node_iterator++;
    }
}

M_TNode *tokenize(M_LexNode *head)
{

    M_TNode *token_head = NULL;
    M_TNode *temp = NULL;
    M_LexNode *lexeme_current_node = head;

    while (lexeme_current_node != NULL)
    {

        M_TNode *new_token_node = malloc(sizeof(M_TNode));
        new_token_node->data = malloc(sizeof(M_Token));
        new_token_node->data->token_value = malloc(strlen(lexeme_current_node->value) + 1);
        new_token_node->next = NULL;

        if (new_token_node->data == NULL || new_token_node->data->token_value == NULL)
        {
            fprintf(stderr, "ERROR: mallocating lexed_tokens or its value failed");
            free(new_token_node->data->token_value);
            free(new_token_node->data);
            free(new_token_node);
            exit(EXIT_FAILURE);
        }

        strcpy(new_token_node->data->token_value, lexeme_current_node->value);

        if (strcmp(lexeme_current_node->value, "function") == 0)
        {
            new_token_node->data->token_type = T_KEYWORD;
        }
        else if (is_number(lexeme_current_node->value))
        {
            new_token_node->data->token_type = T_INTEGER_LITERAL;
        }
        else if (strcmp(lexeme_current_node->value, "(") == 0)
        {
            new_token_node->data->token_type = T_LPAREN;
        }
        else if (strcmp(lexeme_current_node->value, ":") == 0)
        {
            new_token_node->data->token_type = T_COLON;
        }
        else if (strcmp(lexeme_current_node->value, ")") == 0)
        {
            new_token_node->data->token_type = T_RPAREN;
        }
        else if (strcmp(lexeme_current_node->value, ",") == 0)
        {
            new_token_node->data->token_type = T_COMMA;
        }
        else if (strcmp(lexeme_current_node->value, "int") == 0)
        {
            new_token_node->data->token_type = T_KEYWORD;
        }
        else if (strcmp(lexeme_current_node->value, "char") == 0)
        {
            new_token_node->data->token_type = T_KEYWORD;
        }
        else if (strcmp(lexeme_current_node->value, "int[]") == 0)
        {
            new_token_node->data->token_type = T_KEYWORD;
        }
        else if (strcmp(lexeme_current_node->value, "return") == 0)
        {
            new_token_node->data->token_type = T_KEYWORD;
        }
        else if (strcmp(lexeme_current_node->value, ";") == 0)
        {
            new_token_node->data->token_type = T_SEMI_COLON;
        }
        else if (strcmp(lexeme_current_node->value, "{") == 0)
        {
            new_token_node->data->token_type = T_LCURL;
        }
        else if (strcmp(lexeme_current_node->value, "}") == 0)
        {
            new_token_node->data->token_type = T_RCURL;
        }
        else
        {
            new_token_node->data->token_type = T_IDENTIFIER;
        }
        if (token_head == NULL)
        {
            token_head = new_token_node;
            temp = token_head;
        }
        else
        {
            temp->next = new_token_node;
            temp = temp->next;
        }
        lexeme_current_node = lexeme_current_node->next;
    }

    return token_head;
}