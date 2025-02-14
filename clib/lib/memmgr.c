#include "clib.h"

/// TODO: Compute this value at link-time.
static unsigned int next_free_mem = 0x10000;

void *mem_alloc(unsigned int size)
{
    unsigned int alloc = MEM_PAGE_SIZE;
    unsigned int addr;

    if (size / MEM_PAGE_SIZE > 0)
        alloc += MEM_PAGE_SIZE * (size / MEM_PAGE_SIZE);
    addr = next_free_mem;
    next_free_mem += alloc;
    return (void *)(long)addr;
}
