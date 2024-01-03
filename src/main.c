#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../include/file.h"
#include "../include/tokenizer.h"
#include "../include/lexer.h"
#include "../include/parser.h"
#include "../include/cgen.h"

void usage(char *argv[])
{
    printf("USAGE: %s <path/to/inputfile.mon> \n", argv[0]);
}

int main(int argc, char *argv[])
{

    if (argc < 2)
    {
        fprintf(stderr, "ERROR: Incorrect usage, less arguments than expected. \n");
        usage(argv);
        return EXIT_FAILURE;
    }

    const char *const path_to_src_file = argv[1];

    M_File *new_file = get_file(path_to_src_file);

    // TEST ----------
    printf("Word count : %d \n", new_file->word_count);
    printf("contents : %s \n", new_file->contents);

    M_LexNode *lexeme_head = lex(new_file->contents);
    M_TNode *token_head = tokenize(lexeme_head);

    // free initial lexeme_root
    free_lexemes(lexeme_head);
    display_tokens(token_head);

    NodeFunction *parsed = parse_into_converted_function(token_head);
    printf("%s %s (", parsed->type->data->token_value, parsed->identifier->data->token_value);

    if (parsed->param_head == NULL)
    {
        printf("NO PARAMS");
    }
    else
    {
        ParamNode *temp = parsed->param_head;
        while (temp != NULL)
        {
            printf("%s %s , ", temp->data->type->data->token_value, temp->data->identifier->data->token_value);
            temp = temp->next_param;
        }
        printf(")");
    }

    return EXIT_SUCCESS;
}