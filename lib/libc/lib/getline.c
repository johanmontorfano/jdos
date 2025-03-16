#include "kernel/buffers.h"
#include "libc.h"

/// Read stdin until a '\n' is typed. Encountering a '\n' will automatically
/// provoke a flush. The dest will be automatically allocated.
///
/// getline returns the number of bytes read.
int getline(char **dest)
{
    uint32_t size = 0;

    while (stdin[stdin_size - 1] != '\n');
    stdin[stdin_size - 1] = 0;
    size = s_strlen(stdin);
    *dest = mem_alloc(sizeof(char) * (size + 1));
    mem_copy((uint8_t *)stdin, (uint8_t *)dest, size);
    return size;
}
