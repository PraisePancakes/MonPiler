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
    new_token->token_type = 0;

    return new_token;
}

M_TNode *tokenize(int token_count, char *contents)
{
    M_TNode *root = NULL;

    int current_token_index = 0;
    for (int i = 0; i < strlen(contents); i++)
    {
        while (isspace(contents[i]))
        {
            i++;
        }

        if (!isspace(contents[i]) && contents[i] != '(' && contents[i] != ')' && contents[i] != ',' && contents[i] != ';')
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

            M_Token *new_token = init_token(buffer);
            M_TNode *new_token_node = malloc(sizeof(M_TNode));
            new_token_node->token_data = new_token;
            new_token_node->next = NULL;

            if (root == NULL)
            {
                root = new_token_node;
            }
            else
            {
                M_TNode *node_iterator = root;
                while (node_iterator->next != NULL)
                {
                    node_iterator = node_iterator->next;
                }
                node_iterator->next = new_token_node;
            }
        }

        if (contents[i] == '(' || contents[i] == ')' || contents[i] == ',' || contents[i] == ';')
        {
            char specialBuffer[2];
            specialBuffer[0] = contents[i];
            specialBuffer[1] = '\0';

            M_Token *new_token = init_token(specialBuffer);
            M_TNode *new_token_node = malloc(sizeof(M_TNode));
            new_token_node->token_data = new_token;
            new_token_node->next = NULL;

            if (root == NULL)
            {
                root = new_token_node;
            }
            else
            {
                M_TNode *node_iterator = root;
                while (node_iterator->next != NULL)
                {
                    node_iterator = node_iterator->next;
                }
                node_iterator->next = new_token_node;
            }
        }
    }

    return root;
}

void free_tokens(M_TNode *root)
{
    M_TNode *current = root;
    while (current != NULL)
    {
        M_TNode *next = current->next;
        free(current->token_data->value);
        free(current->token_data);
        free(current);
        current = next;
    }
}
