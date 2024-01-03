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

void run_gcc_executable()
{
    system("gcc gen.c -o gen");
    system("gen.exe");
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

    M_LexNode *lexeme_head = lex(new_file->contents);
    M_TNode *token_head = tokenize(lexeme_head);

    // free initial lexeme_root
    free_lexemes(lexeme_head);
    // display_tokens(token_head);

    NodeFunction *root = parse_into_converted_function(token_head);
    Program *parsed_program = parse_program(root);

    char *parsed_to_string = stringify_parsed_program(parsed_program);
    M_CFile *converted_file = get_gcc_compatabile_file(parsed_to_string);

    write_to_gcc_compatible_file(converted_file);

    run_gcc_executable();

    return EXIT_SUCCESS;
}