#include "../include/lexer.h"
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
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

static char peek(const char *const src, size_t current_index)
{
  const size_t byte_offset = 1;

  if (current_index > strlen(src))
  {
    return '\0';
  }
  return src[current_index];
}

static char consume(const char *const src, size_t *current_index)
{
  return src[(*current_index)++];
}

static bool is_punctuation(char c)
{
  return (c == '(' || c == ')' || c == ',' || c == ';' || c == ':' || c == '{' || c == '}');
}

M_LexNode *lex(char *contents)
{
  M_LexNode *root = NULL;

  int i = 0;

  while (peek(contents, i) != '\0')
  {
    char current_character = peek(contents, i);
    while (isspace(current_character))
    {
      consume(contents, &i);
      current_character = peek(contents, i);
    }
    switch (current_character)
    {
    case ';':
    case ':':
    case ',':
    case '(':
    case ')':
    case '{':
    case '}':
    {
      char special_buf[2];
      special_buf[0] = consume(contents, &i);
      special_buf[1] = '\0';
      add_to_lexeme_llist(&root, special_buf);
      break;
    }
    default:
    {
      char buf[BUFFER_SIZE];
      int j = 0;

      while (!isspace(current_character) && !is_punctuation(current_character))
      {
        buf[j++] = consume(contents, &i);
        current_character = peek(contents, i);
      }
      buf[j] = '\0';
      add_to_lexeme_llist(&root, buf);
      break;
    }
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
