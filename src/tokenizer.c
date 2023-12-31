
#include "../include/tokenizer.h"
#include "../include/lexer.h"
#include "../include/hash.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
void display_tokens(M_TNode *head)
{
    M_TNode *temp = head;
    size_t node_iterator = 0;
    const char *types[] = {
        "T_AND",
        "T_ARROW",
        "T_BANG",
        "T_BANG_EQUALS",
        "T_CHAR",
        "T_CHAR_ARRAY",
        "T_COLON",
        "T_COMMA",
        "T_DOT",
        "T_DOUBLE",
        "T_DOUBLE_ARRAY",
        "T_ELSE",
        "T_EQUAL",
        "T_EQUAL_EQUAL",
        "T_FALSE",
        "T_FLOAT",
        "T_FLOAT_ARRAY",
        "T_FOR",
        "T_FUNCTION",
        "T_GT",
        "T_IDENTIFIER_LITERAL",
        "T_IF",
        "T_INT",
        "T_INT_ARRAY",
        "T_INTEGER_LITERAL",
        "T_LBRACE",
        "T_LCURL",
        "T_LPAREN",
        "T_LT",
        "T_MINUS",
        "T_NULL",
        "T_OR",
        "T_PLUS",
        "T_PRINT",
        "T_RETURN",
        "T_RBRACE",
        "T_RCURL",
        "T_RPAREN",
        "T_SEMI_COLON",
        "T_SLASH",
        "T_STAR",
        "T_STRING_LITERAL",
        "T_WHILE",
    };

    while (temp != NULL)
    {
        printf("TOKEN %zu (token_value : %s\t\t\t|| token_type : %s ) \n", node_iterator + 1, temp->data->token_value, types[temp->data->token_type]);
        temp = temp->next;
        node_iterator++;
    }
}

M_TNode *create_token(char *value)
{
    M_TNode *new_token_node = malloc(sizeof(M_TNode));
    new_token_node->data = malloc(sizeof(M_Token));
    new_token_node->data->token_value = malloc(strlen(value) + 1);
    new_token_node->next = NULL;

    if (new_token_node->data == NULL || new_token_node->data->token_value == NULL)
    {
        fprintf(stderr, "ERROR: mallocating lexed_tokens or its value failed");
        free(new_token_node->data->token_value);
        free(new_token_node->data);
        free(new_token_node);
        exit(EXIT_FAILURE);
    }

    return new_token_node;
}

M_TNode *tokenize(M_LexNode *head)
{
    M_TNode *token_head = NULL;
    M_TNode *temp = NULL;
    M_LexNode *lexeme_current_node = head;

    while (lexeme_current_node != NULL)
    {

        M_TNode *new_token_node = create_token(lexeme_current_node->value);

        switch (hash_value_from_key(lexeme_current_node->value))
        {
        case T_STRING_LITERAL:
            new_token_node->data->token_type = T_STRING_LITERAL;

            strcat(new_token_node->data->token_value, lexeme_current_node->value);
            lexeme_current_node = lexeme_current_node->next;

            while (lexeme_current_node != NULL && hash_value_from_key(lexeme_current_node->value) != T_STRING_LITERAL)
            {
                strcat(new_token_node->data->token_value, lexeme_current_node->value);
                if (lexeme_current_node->next != NULL && hash_value_from_key(lexeme_current_node->next->value) != T_STRING_LITERAL)
                {
                    strcat(new_token_node->data->token_value, " ");
                }

                lexeme_current_node = lexeme_current_node->next;
            }

            if (lexeme_current_node != NULL && hash_value_from_key(lexeme_current_node->value) == T_STRING_LITERAL)
            {
                strcat(new_token_node->data->token_value, lexeme_current_node->value);
            }
            else
            {
                fprintf(stderr, "ERROR: Unclosed string literal");
                exit(EXIT_FAILURE);
            }

            break;
        case T_IDENTIFIER_LITERAL:
            new_token_node->data->token_type = T_IDENTIFIER_LITERAL;
            strcpy(new_token_node->data->token_value, lexeme_current_node->value);
            break;
        default:
            new_token_node->data->token_type = hash_value_from_key(lexeme_current_node->value);
            strcpy(new_token_node->data->token_value, lexeme_current_node->value);
            break;
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
