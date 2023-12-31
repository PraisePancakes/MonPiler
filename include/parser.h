#ifndef PARSER_H
#define PARSER_H
#include "tokenizer.h"
#define BUFFER 256

// TO DO :: refactor parser to be more generalized

typedef struct Param
{
    M_TNode *type;
    M_TNode *identifier;
} Param;

typedef struct ParamNode
{
    Param *data;
    struct ParamNode *next_param;
} ParamNode;

typedef struct NodeFunction
{
    M_TNode *type;
    M_TNode *identifier;
    ParamNode *param_head;
    char *contents;

} NodeFunction;

typedef struct Program
{
    NodeFunction *root;
} Program;

NodeFunction *parse_into_converted_function(M_TNode *function_root_node);
Program *parse_program(NodeFunction *root);
char *stringify_parsed_program(Program *parsed_program);

#endif