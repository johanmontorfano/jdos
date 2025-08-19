#include "libc.h"

/// Copy n bytes from source to dest.
void *mem_copy(void *dst, const void *src, uint32_t n) {
    char *ret = dst;
    char *p = dst;
    const char *q = src;
    
    while (n--)
        *p++ = *q++;
    return ret;
}
