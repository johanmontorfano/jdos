#include "drivlib.h"
#include "drivlib/ata.h"
#include "kernel/interrupts.h"
#include "kernel/cpu.h"
#include "kernel/gdt.h"

int main()
{
    char *line;

    clear_screen();
    init_gdt();
    set_kernel_stack(0x9FFFF);
    isr_init();
    irq_init(50);
    init_system_calls();
    init_dma_prdt();
    print("Welcome to Johan's Dumb Operating System :)\n");
    enter_user_mode();
}
