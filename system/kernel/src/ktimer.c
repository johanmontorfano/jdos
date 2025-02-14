#include "kernel/timer.h"
#include "kernel/interrupts.h"
#include "drivlib.h"

unsigned int tick = 0;

static void timcback(t_cpu_reg regs)
{
    tick++;
}

/// Set the PIT to a specific frequency.
void timer_init(unsigned int freq)
{
    unsigned int divisor = HW_CLOCK_HZ / freq;
    unsigned char low = divisor & 0xFF;
    unsigned char high = (divisor >> 8) & 0xFF;

    reg_int_handler(IRQ0, timcback);
    writeb_port(0x43, 0x36);
    writeb_port(0x40, low);
    writeb_port(0x40, high);
}
