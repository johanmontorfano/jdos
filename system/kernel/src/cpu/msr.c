#include "ctypes.h"
#include "kernel/msr.h"

/// MSR (Model-Specific Registers) are special control registers that manages
/// low-level CPU features.
inline void write_msr(uint32_t msr, uint32_t value) {
    asm volatile ("wrmsr" : : "c"(msr), "a"(value), "d"(value >> 32));
}
