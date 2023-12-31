
#include "../include/tokenizer.h"
#include "../include/lexer.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../include/hash.h"

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
        switch (hash_value_from_key(new_token_node->data->token_value))
        {
        case T_AND:
            new_token_node->data->token_type = T_AND;
            break;
        case T_ARROW:
            new_token_node->data->token_type = T_ARROW;
            break;
        case T_BANG:
            new_token_node->data->token_type = T_BANG;
            break;
        case T_BANG_EQUALS:
            new_token_node->data->token_type = T_BANG_EQUALS;
            break;
        case T_CHAR:
            new_token_node->data->token_type = T_CHAR;
            break;
        case T_CHAR_ARRAY:
            new_token_node->data->token_type = T_CHAR_ARRAY;
            break;
        case T_COLON:
            new_token_node->data->token_type = T_COLON;
            break;
        case T_COMMA:
            new_token_node->data->token_type = T_COMMA;
            break;
        case T_DOT:
            new_token_node->data->token_type = T_DOT;
            break;
        case T_DOUBLE:
            new_token_node->data->token_type = T_DOUBLE;
            break;
        case T_DOUBLE_ARRAY:
            new_token_node->data->token_type = T_DOUBLE_ARRAY;
            break;
        case T_ELSE:
            new_token_node->data->token_type = T_ELSE;
            break;
        case T_EQUAL:
            new_token_node->data->token_type = T_EQUAL;
            break;
        case T_EQUAL_EQUAL:
            new_token_node->data->token_type = T_EQUAL_EQUAL;
            break;
        case T_FALSE:
            new_token_node->data->token_type = T_FALSE;
            break;
        case T_FLOAT:
            new_token_node->data->token_type = T_FLOAT;
            break;
        case T_FLOAT_ARRAY:
            new_token_node->data->token_type = T_FLOAT_ARRAY;
            break;
        case T_FOR:
            new_token_node->data->token_type = T_FOR;
            break;
        case T_FUNCTION:
            new_token_node->data->token_type = T_FUNCTION;
            break;
        case T_GT:
            new_token_node->data->token_type = T_GT;
            break;
        case T_IF:
            new_token_node->data->token_type = T_IF;
            break;
        case T_INT:
            new_token_node->data->token_type = T_INT;
            break;
        case T_INT_ARRAY:
            new_token_node->data->token_type = T_INT_ARRAY;
            break;
        case T_INTEGER_LITERAL:
            new_token_node->data->token_type = T_INTEGER_LITERAL;
            break;
        case T_LBRACE:
            new_token_node->data->token_type = T_LBRACE;
            break;
        case T_LCURL:
            new_token_node->data->token_type = T_LCURL;
            break;
        case T_LPAREN:
            new_token_node->data->token_type = T_LPAREN;
            break;
        case T_LT:
            new_token_node->data->token_type = T_LT;
            break;
        case T_MINUS:
            new_token_node->data->token_type = T_MINUS;
            break;
        case T_NULL:
            new_token_node->data->token_type = T_NULL;
            break;
        case T_OR:
            new_token_node->data->token_type = T_OR;
            break;
        case T_PLUS:
            new_token_node->data->token_type = T_PLUS;
            break;
        case T_PRINT:
            new_token_node->data->token_type = T_PRINT;
            break;
        case T_RETURN:
            new_token_node->data->token_type = T_RETURN;
            break;
        case T_RBRACE:
            new_token_node->data->token_type = T_RBRACE;
            break;
        case T_RCURL:
            new_token_node->data->token_type = T_RCURL;
            break;
        case T_RPAREN:
            new_token_node->data->token_type = T_RPAREN;
            break;
        case T_SEMI_COLON:
            new_token_node->data->token_type = T_SEMI_COLON;
            break;
        case T_SLASH:
            new_token_node->data->token_type = T_SLASH;
            break;
        case T_STAR:
            new_token_node->data->token_type = T_STAR;
            break;
        case T_STRING_LITERAL:
            new_token_node->data->token_type = T_STRING_LITERAL;

            break;
        case T_WHILE:
            new_token_node->data->token_type = T_WHILE;
            break;
        default:
            new_token_node->data->token_type = T_IDENTIFIER_LITERAL;
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