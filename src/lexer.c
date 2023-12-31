#include "../include/lexer.h"
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>
#define BUFFER_SIZE 1024

static M_LexNode *init_lexeme(char *value)
{
  M_LexNode *new_lexeme = malloc(sizeof(M_LexNode));
  new_lexeme->value = malloc(strlen(value) + 1);
  strcpy(new_lexeme->value, value);
  new_lexeme->next = NULL;

  return new_lexeme;
}

static void add_to_lexeme_llist(M_LexNode **root, char *value)
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

static char lexer_peek(const char *const src, size_t current_index)
{
  const size_t byte_offset = 1;

  if (current_index > strlen(src))
  {
    return '\0';
  }
  return src[current_index];
}

static char lexer_consume(const char *const src, size_t *current_index)
{
  return src[(*current_index)++];
}

static bool is_punctuation(char c)
{
  return (c == '(' || c == ')' || c == ',' || c == ';' || c == ':' || c == '{' || c == '}' || c == '\"'); // TO DO add more punctuators maybe 'switch' it up?
}

M_LexNode *lex(char *contents)
{
  M_LexNode *root = NULL;

  int i = 0;

  while (lexer_peek(contents, i) != '\0')
  {
    char current_character = lexer_peek(contents, i);
    while (isspace(current_character))
    {
      lexer_consume(contents, &i);
      current_character = lexer_peek(contents, i);
    }

    if (is_punctuation(current_character))
    {
      char punctuation_buf[2];
      punctuation_buf[0] = lexer_consume(contents, &i);
      punctuation_buf[1] = '\0';
      add_to_lexeme_llist(&root, punctuation_buf);
    }
    else
    {
      char buf[BUFFER_SIZE];
      int j = 0;

      while (!isspace(current_character) && !is_punctuation(current_character))
      {
        buf[j++] = lexer_consume(contents, &i);
        current_character = lexer_peek(contents, i);
      }
      buf[j] = '\0';
      add_to_lexeme_llist(&root, buf);
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
