#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define BUFFER_SIZE 1024

typedef struct File
{
    int word_count;
    char *contents;
    int length;

} File;

File *get_file(const char *const filepath)
{
    FILE *fp = fopen(filepath, "r");
    if (fp == NULL)
    {
        fprintf(stderr, "ERROR: file path %s could not be opened for reading \n", filepath);
        fclose(fp);
        return NULL;
    }
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

    fseek(fp, 0, SEEK_SET);

    char *filestream_buf = malloc(file_length + 1);
    int i = 0;

    do
    {
        c = fgetc(fp);
        filestream_buf[i] = c;
        i++;
    } while (i != file_length);

    filestream_buf[i] = '\0';

    File *file = malloc(sizeof(File));

    file->contents = malloc(strlen(filestream_buf) + 1);
    strcpy(file->contents, filestream_buf);

    file->length = file_length;

    fclose(fp);
    return file;
}

int main(int argc, char *argv[])
{

    if (argc < 2)
    {
        fprintf(stderr, "ERROR: Incorrect usage, ./mon <path/to/inputfile.mon> \n");
        return 1;
    }

    const char *const path_to_src_file = argv[1];

    File *new_file = get_file(path_to_src_file);

    printf("%s", new_file->contents);

    return EXIT_SUCCESS;
}