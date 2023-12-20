#include "../include/tokenizer.h"
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#define BUFFER_SIZE 1024

M_Token *init_token(char *value)
{
    M_Token *new_token = malloc(sizeof(M_Token));
    new_token->value = malloc(strlen(value) + 1);
    strcpy(new_token->value, value);
    new_token->value = 0;

    return new_token;
}

M_Token *tokenize(int token_count, char *contents)
{

    M_Token *tokens = malloc(token_count * sizeof(M_Token)); // Adjust the size accordingly
    int current_token_index = 0;
    for (int i = 0; i < strlen(contents); i++)
    {

        while (isspace(contents[i]))
        {
            i++;
        }

        if (!isspace(contents[i]))
        {
            char buffer[BUFFER_SIZE];
            int j = 0;
            while (!isspace(contents[i]) && contents[i] != '(' && contents[i] != ')' && contents[i] != ',' && contents[i] != ';')
            {
                buffer[j] = contents[i];
                i++;
                j++;
            }
            buffer[j] = '\0';

            M_Token token;
            token.value = strdup(buffer);
            token.token_type = 0;
            tokens[current_token_index++] = token;
        }

        if (contents[i] == '(' || contents[i] == ')' || contents[i] == ',' || contents[i] == ';')
        {
            char specialBuffer[2];
            specialBuffer[0] = contents[i];
            specialBuffer[1] = '\0';

            M_Token specialToken; // maybe use pointer to m_token here instead, that way we can free it
            specialToken.value = strdup(specialBuffer);
            specialToken.token_type = 0;
            tokens[current_token_index++] = specialToken;
        }
    }

    return tokens;
}

void free_token_array(int token_count, M_Token *token_array)
{
    for (int i = 0; i < token_count; i++)
    {
        free(token_array[i].value);
    }

    free(token_array);
}