#include "devices/raw.h"
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

// Creates a new stdin for the sake of a sane input
char *_getinput(uint8_t silent)
{
    char *stdin_copy = mem_alloc(stdin_size);
    uint32_t copy_size = stdin_size;

    mem_copy(stdin_copy, stdin, stdin_size);
    stdin_size = 0;
    kb_explicit_mode = !silent;
    while (stdin[stdin_size - 1] != '\n');

    char *out = mem_alloc(stdin_size);

    mem_copy(out, stdin, stdin_size);
    // we replace the \n with nothing
    out[stdin_size - 1] = 0;
    kb_explicit_mode = 0;
    mem_copy(stdin, stdin_copy, copy_size);
    stdin_size = copy_size;
    return out; 
}

char *getinputsilent()
{
    return _getinput(1);
}

char *getinput()
{
    return _getinput(0);
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
