#include "clib.h"

/// Copy n bytes from source to dest.
void mem_copy(unsigned char *source, unsigned char *dest, int n)
{
    int i = 0;

    while (i < n) {
        dest[i] = source[i];
        i++;
    }
}
