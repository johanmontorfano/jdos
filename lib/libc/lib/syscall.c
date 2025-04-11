#include "libc.h"

/// This function aims at invoking `sysenter` from user mode.
inline void syscall(int syscall_nb)
{
    asm volatile (
        "mov %0, %%eax\n"
        "sysenter"
        : : "r"(syscall_nb) : "eax"
    );
}
