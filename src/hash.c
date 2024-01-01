#include "../include/hash.h"
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

static bool is_number(char *src)
{
    for (int i = 0; i < strlen(src); i++)
    {
        if (!isdigit(src[i]))
        {
            return false;
        }
    }
    return true;
}

int hash_value_from_key(char *key)
{
    int i;
    if (is_number(key))
    {
        return T_INTEGER_LITERAL;
    }
    for (i = 0; i < NKEYS; i++)
    {
        M_THash *string = lookuptable + i;
        if (strcmp(string->key, key) == 0)
        {
            return string->value;
        }
    }

    return IDENTIFIER;
}