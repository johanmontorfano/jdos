#include "kernel/buffers.h"
#include "ctypes.h"
#include "libc.h"

/// `stdin` contains data written to by different components - including the
/// keyboard. To allow implementing dynamic sizing later with the kernel, es-
/// -pecially through `mem_realloc`, I choose to initialize `stdin` with a
/// custom function `init_stdin`.
char *stdin;
uint32_t stdin_size = 0;

void stdin_write(char c)
{
    stdin[stdin_size] = c;
    stdin_size++;
}

/// Stdin is not really flushed since data remains, the pointer is just reset.
void stdin_flush(void)
{
    stdin_size = 0;
}

void stdin_init(void)
{
    stdin = mem_alloc(sizeof(char) * 1000);
}
