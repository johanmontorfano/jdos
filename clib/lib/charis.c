#include "stdlib.h"

int c_isnum(char c)
{
    return c >= '0' && c <= '9';
}

int c_isalpha(char c)
{
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

int c_isalphanum(char c)
{
    return c_isnum(c) || c_isalpha(c);
}
