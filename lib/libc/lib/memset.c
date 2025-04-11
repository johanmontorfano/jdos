#include "libc.h"
#include "ctypes.h"

void *mem_set(void *dest, register int val, register size_t len)
{
    register uint8_t *ptr = (uint8_t *)dest;

    while (len-- > 0)
        *ptr++  = val;
    return dest;
}
