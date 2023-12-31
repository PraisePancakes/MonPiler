// hash a string to a key : value
#ifndef HASH_H
#define HASH_H
#define BADKEY -1
enum M_TOKEN_TYPE
{
    T_AND,
    T_ARROW,
    T_BANG,
    T_BANG_EQUALS,
    T_CHAR,
    T_CHAR_ARRAY,
    T_COLON,
    T_COMMA,
    T_DOT,
    T_DOUBLE,
    T_DOUBLE_ARRAY,
    T_ELSE,
    T_EQUAL,
    T_EQUAL_EQUAL,
    T_FALSE,
    T_FLOAT,
    T_FLOAT_ARRAY,
    T_FOR,
    T_FUNCTION,
    T_GT,
    T_IDENTIFIER_LITERAL,
    T_IF,
    T_INT,
    T_INT_ARRAY,
    T_INTEGER_LITERAL,
    T_LBRACE,
    T_LCURL,
    T_LPAREN,
    T_LT,
    T_MINUS,
    T_NULL,
    T_OR,
    T_PLUS,
    T_PRINT,
    T_RETURN,
    T_RBRACE,
    T_RCURL,
    T_RPAREN,
    T_SEMI_COLON,
    T_SLASH,
    T_STAR,
    T_STRING_LITERAL,
    T_WHILE,
} token_type;

typedef struct t_symstruct
{
    char *key;
    int value;
} t_symstruct;

static t_symstruct lookuptable[] = {
    {"&&", T_AND},
    {"->", T_ARROW},
    {"!", T_BANG},
    {"!=", T_BANG_EQUALS},
    {"char", T_CHAR},
    {"char[]", T_CHAR_ARRAY},
    {":", T_COLON},
    {",", T_COMMA},
    {".", T_DOT},
    {"double", T_DOUBLE},
    {"double[]", T_DOUBLE_ARRAY},
    {"else", T_ELSE},
    {"=", T_EQUAL},
    {"==", T_EQUAL_EQUAL},
    {"false", T_FALSE},
    {"float", T_FLOAT},
    {"float[]", T_FLOAT_ARRAY},
    {"for", T_FOR},
    {"function", T_FUNCTION},
    {">", T_GT},
    {"identifier_literal", T_IDENTIFIER_LITERAL}, // Assuming this is a placeholder for other identifiers
    {"if", T_IF},
    {"int", T_INT},
    {"int[]", T_INT_ARRAY},
    {"integer_literal", T_INTEGER_LITERAL},
    {"{", T_LBRACE},
    {"{", T_LCURL},
    {"(", T_LPAREN},
    {"<", T_LT},
    {"-", T_MINUS},
    {"NULL", T_NULL},
    {"||", T_OR},
    {"+", T_PLUS},
    {"print", T_PRINT},
    {"return", T_RETURN},
    {"}", T_RBRACE},
    {"}", T_RCURL},
    {")", T_RPAREN},
    {";", T_SEMI_COLON},
    {"/", T_SLASH},
    {"*", T_STAR},
    {"\"", T_STRING_LITERAL}, // fix this
    {"while", T_WHILE},
};

#define NKEYS (sizeof(lookuptable) / sizeof(t_symstruct))

int hash_value_from_key(char *key);

#endif