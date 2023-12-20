#include "../include/file.h"
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int get_file_length(FILE *fp)
{
    char c;
    int file_length = 0;

    while (c = fgetc(fp) != EOF)
    {
        file_length++;
    }

    if (file_length == 0)
    {
        printf("ERROR :: CANNOT PARSE EMPTY FILE\n");
        fclose(fp);
        exit(EXIT_FAILURE);
    }

    return file_length;
}

char *get_file_contents(FILE *fp, int file_length)
{

    char *filestream_buf = malloc(file_length + 1);
    int i = 0;
    char c;
    do
    {
        c = fgetc(fp);
        filestream_buf[i] = c;
        i++;
    } while (i != file_length);

    filestream_buf[i] = '\0';

    return filestream_buf;
}

M_File *get_file(const char *const filepath)
{
    FILE *fp = fopen(filepath, "r");
    if (fp == NULL)
    {
        fprintf(stderr, "ERROR: file path %s could not be opened for reading \n", filepath);
        fclose(fp);
        return NULL;
    }
    int file_length = get_file_length(fp);

    fseek(fp, 0, SEEK_SET);

    char *filestream_buf = get_file_contents(fp, file_length);

    M_File *file = malloc(sizeof(M_File));

    file->contents = malloc(strlen(filestream_buf) + 1);
    strcpy(file->contents, filestream_buf);
    file->length = file_length;

    fclose(fp);
    return file;
}

int get_file_word_count(M_File *file)
{
    int word_count = 0;
    for (int i = 0; i < file->length; i++)
    {
        // get rid of leading spaces

        while (isspace(file->contents[i]))
        {
            i++;
        }

        if (!isspace(file->contents[i]))
        {
            while (!isspace(file->contents[i]))
            {
                i++;
            }
            word_count++;
        }
    }

    return word_count;
}

int get_file_token_count(M_File *file)
{
    int token_count = 0;
    for (int i = 0; i < strlen(file->contents); i++)
    {
        while (isspace(file->contents[i]))
        {
            i++;
        }

        if (!isspace(file->contents[i]))
        {

            while (!isspace(file->contents[i]) && file->contents[i] != '(' && file->contents[i] != ')' && file->contents[i] != ',' && file->contents[i] != ';')
            {

                i++;
            }
            token_count++;
        }

        if (file->contents[i] == '(' || file->contents[i] == ')' || file->contents[i] == ',' || file->contents[i] == ';')
        {
            token_count++;
        }
    }

    return token_count;
};