#include "kernel/cpu.h"
#include "libc.h"

int usermode()
{
    syscall(1);
    while (1);
}
