#include "../include/parser.h"
#include "../include/hash.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

NodeFunction *parse_into_converted_function(M_TNode *function_root_node)
{
    NodeFunction *parsed_function = malloc(sizeof(NodeFunction));
    parsed_function->type = malloc(sizeof(M_TNode));
    parsed_function->identifier = malloc(sizeof(M_TNode));

    M_TNode *temp = function_root_node;

    // get func signature
    while (temp != NULL && temp->data->token_type != T_LPAREN)
    {
        switch (hash_value_from_key(temp->data->token_value))
        {
        case T_INT:
            parsed_function->type = temp;
            break;
        case T_IDENTIFIER_LITERAL:
            parsed_function->identifier = temp;
            break;
        default:
            break;
        }
        temp = temp->next;
    }

    // get params
    // temp = (
    // if params enter while
    temp = temp->next;
    M_TNode *param_iterator = temp;
    // temp = 'a'
    parsed_function->param_head = NULL;

    while (param_iterator != NULL && param_iterator->data->token_type != T_RPAREN)
    {
        ParamNode *new_node = malloc(sizeof(ParamNode));
        new_node->data = malloc(sizeof(Param));

        while (hash_value_from_key(param_iterator->data->token_value) != T_COMMA && param_iterator->data->token_type != T_RPAREN)
        {

            if (hash_value_from_key(param_iterator->data->token_value) == T_COLON)
            {
                param_iterator = param_iterator->next;
                continue;
            }
            switch (hash_value_from_key(param_iterator->data->token_value))
            {
            case T_IDENTIFIER_LITERAL:
                new_node->data->identifier = param_iterator;
                break;
            default:
                new_node->data->type = param_iterator;
                break;
            }

            param_iterator = param_iterator->next;
        }
        if (parsed_function->param_head == NULL)
        {
            parsed_function->param_head = new_node;
            new_node->next_param = NULL;
        }
        else
        {
            ParamNode *iterator = parsed_function->param_head;
            while (iterator->next_param != NULL)
            {
                iterator = iterator->next_param;
            }
            iterator->next_param = malloc(sizeof(ParamNode));
            iterator->next_param->data = malloc(sizeof(Param));
            iterator->next_param->next_param = NULL;
            iterator->next_param->data = new_node->data;
        }
        if (param_iterator->data->token_type == T_RPAREN)
        {
            break;
        }
        else
        {
            param_iterator = param_iterator->next;
        }
    }

    // get contents

    return parsed_function;
}