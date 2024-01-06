#include "../include/parser.h"
#include "../include/hash.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char *parse_into_converted_expr(M_TNode *current_token)
{

    M_TNode *temp = current_token;

    if (temp->next->data->token_type != T_COLON)
    {
        return current_token->data->token_value;
    }

    int ident_length = strlen(temp->data->token_value);
    char ident_buf[ident_length + 1];
    strcpy(ident_buf, temp->data->token_value);

    int type_len = 0;
    char *type_buf = NULL;

    while (temp != NULL && temp->data->token_type != T_SEMI_COLON)
    {
        if (temp->data->token_type == T_COLON)
        {
            temp = temp->next;
            continue;
        }

        switch (temp->data->token_type)
        {
        case T_INT:
        case T_FLOAT:
        case T_INT_ARRAY:
        case T_FLOAT_ARRAY:
        case T_DOUBLE_ARRAY:
        case T_CHAR:
        case T_CHAR_ARRAY:
            type_len = strlen(temp->data->token_value);
            type_buf = malloc(type_len + 1);
            strcpy(type_buf, temp->data->token_value);
            break;

        default:
            break;
        }

        temp = temp->next;
    }

    char *parsed_expr = malloc(ident_length + type_len + 1); // +2 for '=' and null terminator
    parsed_expr[0] = '\0';

    strcat(parsed_expr, type_buf);
    strcat(parsed_expr, " ");
    strcat(parsed_expr, ident_buf);

    return parsed_expr;
}

NodeFunction *parse_into_converted_function(M_TNode *function_root_node)
{
    NodeFunction *parsed_function = malloc(sizeof(NodeFunction));
    parsed_function->type = malloc(sizeof(M_TNode));
    parsed_function->identifier = malloc(sizeof(M_TNode));

    M_TNode *token_iterator = function_root_node;

    // get func signature
    while (token_iterator != NULL && token_iterator->data->token_type != T_LPAREN)
    {
        switch (hash_value_from_key(token_iterator->data->token_value))
        {
        case T_INT:
            parsed_function->type = token_iterator;
            break;
        case T_IDENTIFIER_LITERAL:
            parsed_function->identifier = token_iterator;
            break;
        default:
            break;
        }
        token_iterator = token_iterator->next;
    }

    // get params
    // token_iterator = (
    // if params enter while
    token_iterator = token_iterator->next;
    M_TNode *param_iterator = token_iterator;
    // token_iterator = 'a'
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

    token_iterator = param_iterator->next;

    M_TNode *body_iterator = token_iterator; // -> {
    char content_buf[2048];
    content_buf[0] = '\0';

    while (body_iterator != NULL)
    {
        switch (body_iterator->data->token_type)
        {
        case T_IDENTIFIER_LITERAL:
        {
            char *parsed_expression = parse_into_converted_expr(body_iterator);
            strcat(content_buf, parsed_expression);
        }

        break;
        case T_INTEGER_LITERAL:
            strcat(content_buf, " ");
            strcat(content_buf, body_iterator->data->token_value);
            break;
        case T_LBRACE:
        case T_LPAREN:
        case T_RPAREN:
        case T_PRINT:
        case T_STRING_LITERAL:
        case T_EQUAL:
        case T_RETURN:
        case T_PLUS:
        case T_RBRACE:
        case T_COMMA:
        case T_SEMI_COLON:
            strcat(content_buf, body_iterator->data->token_value);
            break;
        default:
            break;
        }

        body_iterator = body_iterator->next;
    }

    parsed_function->contents = malloc(strlen(content_buf) + 1);

    strcpy(parsed_function->contents, content_buf);
    return parsed_function;
}

Program *parse_program(NodeFunction *root)
{
    Program *prog = malloc(sizeof(Program));
    prog->root = root;
    return prog;
}

char *stringify_parsed_program(Program *parsed_program)
{

    char *prog_buf = malloc(2048 * sizeof(char));
    prog_buf[0] = '\0';
    strcat(prog_buf, "#include <stdio.h>\n");
    strcat(prog_buf, "#include <stdlib.h>\n");

    strcat(prog_buf, parsed_program->root->type->data->token_value); // int
    strcat(prog_buf, " ");
    strcat(prog_buf, parsed_program->root->identifier->data->token_value); // main
    strcat(prog_buf, "(");

    ParamNode *temp = parsed_program->root->param_head;
    while (temp != NULL)
    {
        strcat(prog_buf, temp->data->type->data->token_value);
        strcat(prog_buf, " ");
        strcat(prog_buf, temp->data->identifier->data->token_value);

        // Check if there is another parameter before adding a comma
        if (temp->next_param != NULL)
        {
            strcat(prog_buf, ",");
        }

        temp = temp->next_param;
    }

    strcat(prog_buf, ")");

    strcat(prog_buf, parsed_program->root->contents);

    return prog_buf;
}