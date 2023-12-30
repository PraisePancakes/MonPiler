#include "../include/tokenizer.h"
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#define BUFFER_SIZE 1024

M_LexNode *init_lexeme(char *value)
{
  M_LexNode *new_lexeme = malloc(sizeof(M_LexNode));
  new_lexeme->value = malloc(strlen(value) + 1);
  strcpy(new_lexeme->value, value);
  new_lexeme->next = NULL;

  return new_lexeme;
}

void add_to_lexeme_llist(M_LexNode **root, char *value)
{
  M_LexNode *new_lex_node = init_lexeme(value);

  if (*root == NULL)
  {
    *root = new_lex_node;
  }
  else
  {
    M_LexNode *node_iterator = *root;
    while (node_iterator->next != NULL)
    {
      node_iterator = node_iterator->next;
    }
    node_iterator->next = new_lex_node;
  }
}

/*
for (int i = 0; i < strlen(src); i++) {
    while (peek(src, i) == '\0') {
      i++;
    }
    int buffer_index = 0;
    char buf[MAX_BUFF] = "";
    while (peek(src, i) != '\0') {
      char c = consume(src, i);
      switch (c) {
      case '(':
        char buf[2] = "";
        buf[0] = c;
        buf[1] = '\0'
        add_to_lexeme_llist(&root, buf);
        i++;
        break;
      case ')':
        char buf[2] = "";
        buf[0] = c;
        buf[1] = '\0'
        add_to_lexeme_llist(&root, buf);
        i++;
        break;
      case ',':
        char buf[2] = "";
        buf[0] = c;
        buf[1] = '\0'
        add_to_lexeme_llist(&root, buf);
        i++;
        break;
      case ';':
        char buf[2] = "";
        buf[0] = c;
        buf[1] = '\0'
        add_to_lexeme_llist(&root, buf);
        i++;
        break;
        default :
      }
      buf[buffer_index] = c;
      buffer_index++;
      i++;
    }
    buf[buffer_index] = '\0';
    add_to_lexeme_llist(&root, buf);
    printf("%s\n", buf);
  }

*/
// implement peek and consume on characters

char peek(const char *const src, size_t current_index)
{
  const size_t byte_offset = 1;

  if (current_index > strlen(src))
  {
    return '\0';
  }
  return src[current_index];
}

char consume(const char *const src, size_t *current_index)
{

  return src[(*current_index)++];
}

bool is_punctuation(char c)
{
  return (c == '(' || c == ')' || c == ',' || c == ';' || c == ':' || c == '{' || c == '}');
}

M_LexNode *lex(char *contents)
{
  M_LexNode *root = NULL;

  int i = 0;

  while (peek(contents, i) != '\0')
  {
    char c = peek(contents, i);
    while (isspace(c))
    {
      consume(contents, &i);
      c = peek(contents, i);
    }

    if (!is_punctuation(c))
    {
      char buf[BUFFER_SIZE];
      int j = 0;

      while (!isspace(c) && !is_punctuation(c))
      {
        buf[j++] = consume(contents, &i);
        c = peek(contents, i);
      }
      buf[j] = '\0';
      add_to_lexeme_llist(&root, buf);
    }
    else
    {
      char special_buf[2];
      special_buf[0] = consume(contents, &i);
      special_buf[1] = '\0';
      add_to_lexeme_llist(&root, special_buf);
    }
  }

  return root;
}

void free_lexemes(M_LexNode *root)
{
  M_LexNode *current = root;
  while (current != NULL)
  {
    M_LexNode *next = current->next;
    free(current->value);
    free(current);
    current = next;
  }
}
