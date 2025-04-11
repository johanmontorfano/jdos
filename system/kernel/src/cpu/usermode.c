#include "kernel/cpu.h"
#include "libc.h"

int usermode()
{
    write("usermode", 8);
    while (1);
}
