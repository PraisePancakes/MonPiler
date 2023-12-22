#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../include/file.h"
#include "../include/tokenizer.h"
#include "../include/lexer.h"

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
    int word_count = get_file_word_count(new_file);
    int token_count = get_file_token_count(new_file);

    new_file->word_count = word_count;
    M_TNode *token_root = tokenize(new_file->contents);

    // TEST ----------
    printf("Word count : %d \n", word_count);
    printf("contents : %s \n", new_file->contents);

    Lexer *lexed_tokens = lex_tokens(token_root);

    // free initial UNLEXED toke_root
    free_tokens(token_root);

    display_lexed_tokens(lexed_tokens);

    return EXIT_SUCCESS;
}