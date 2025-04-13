#include "kernel/cpu.h"
#include "ctypes.h"
#include "libc.h"

/// Initializing the system call engine is mandatory and is done here.
void init_system_calls(void)
{
    write_msr(0x174, 0x08);
    write_msr(0x175, 0x900000);
    write_msr(0x176, (uint32_t)syscall_entry);
}

/// System calls are used by applications to communicate with the kernel, hence
/// reducing the number of operations an application can do that could harm
/// the system integrity.
/// Even though this system calls engine is not really complete and will miss
/// many aspects of a real implementation, it aims at being a first step
/// towards application execution. To do a system call, a function in `libc`
/// called `syscall` will be used:
///     -    to convert the request into a kernel-ready instruction.
///     -    to evaluate the request type, and prevent running if not allowed.
///     -    to convert a system_call result into an expected result.
/// Overall, the `Fast System Call` technique is used to implement system
/// calls.
///
/// function: system_call
/// This function is used directly from assembly to proceed to an operation in
/// kernel mode. Hence this function is always ran in kernel mode.
void system_call(uint32_t syscall_number)
{
}
