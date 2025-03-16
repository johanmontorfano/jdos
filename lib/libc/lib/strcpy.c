#include "libc.h"

/// WARN: Doesn't check if dest is long enough
void s_strcpy(char *dest, char *src)
{
    for (uint32_t i = 0; src && src[i]; i++)
        dest[i] = src[i];
}
