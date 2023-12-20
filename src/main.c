#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../include/file.h"
#include "../include/tokenizer.h"

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
    M_Token *test = tokenize(new_file, new_file->contents);

    printf("Word count : %d \n", word_count);
    printf("Token count : %d \n", new_file->token_count);
    printf("contents : %s", new_file->contents);

    for (int i = 0; i < new_file->token_count; i++)
    {
        printf("%s -> ", test[i].value);
    }

    return EXIT_SUCCESS;
}