#include "libc.h"
#include "ctypes.h"

/// This function aims at invoking `sysenter` from user mode.
inline void syscall(uint32_t syscall_nb)
{
    asm volatile (
        "lea 1f, %%ecx\n"    // Load address of label into ECX
        "mov %%esp, %%edx\n" // Set EDX to user ESP
        "mov %[num], %%eax\n"
        "sysenter\n"
        "1:\n"
        :
        : [num] "r"(syscall_nb)
        : "eax", "ecx", "edx", "memory"
    );
}
