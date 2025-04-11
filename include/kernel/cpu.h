#ifndef CPU_H
    #define CPU_H
    #define HW_CLOCK_HZ 1193180
    #include "ctypes.h"

extern void syscall_entry(void);
void init_system_calls(void);
void system_call(int syscall_number);
void write_msr(uint32_t msr, uint32_t value);
void timer_init(uint32_t freq);

#endif
