#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../include/file.h"
#include "../include/tokenizer.h"
#include "../include/lexer.h"

int main(int argc, char *argv[])
{

    if (argc < 2)
    {
        fprintf(stderr, "ERROR: Incorrect usage, less arguments than expected. \nUsage : ./mon <path/to/inputfile.mon> \n");
        return 1;
    }

    const char *const path_to_src_file = argv[1];

    M_File *new_file = get_file(path_to_src_file);
    int word_count = get_file_word_count(new_file);
    int token_count = get_file_token_count(new_file);

    new_file->word_count = word_count;
    new_file->token_count = token_count;
    M_Token *token_array = tokenize(new_file->token_count, new_file->contents);

    printf("Word count : %d \n", word_count);
    printf("Token count : %d \n", new_file->token_count);
    printf("contents : %s \n", new_file->contents);

    Lexer *lexed_token_array = lex_tokens(new_file->token_count, token_array);

    for (int i = 0; i < new_file->token_count; i++)
    {
        printf("[ %s -- %d ]-> ", lexed_token_array->token_array[i].value, lexed_token_array->token_array[i].token_type);
    }

    return EXIT_SUCCESS;
}