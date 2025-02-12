#include "stdlib.h"

int c_isnum(char c)
{
    return c >= '0' && c <= '9';
}

int c_isalpha(char c)
{
    return c_isalphaup(c) || c_isalphalow(c);
}

int c_isalphanum(char c)
{
    return c_isnum(c) || c_isalpha(c);
}

int c_isspace(char c)
{
    return c == ' ' || c == '\t' || c == '\n';
}

int c_isalphalow(char c)
{
    return c >= 'a' && c <= 'z';
}

int c_isalphaup(char c)
{
    return c >= 'A' && c <= 'Z';
}

int c_isprintable(char c)
{
    return c > 31 && c < 127;
}
