#include "clib.h"

void mem_set(unsigned char *dest, unsigned int size)
{
    unsigned char *tmp = dest;

    while (size > 0) {
        *tmp = 0;
        tmp++;
        size--;
    }
}
