#include "drivlib.h"
#include "drivlib/ata.h"
#include "kernel/interrupts.h"
#include "kernel/cpu.h"
#include "kernel/gdt.h"

int main()
{
    char *line;

    clear_screen();
    load_kernel_gdt();
    isr_init();
    irq_init(50);
    init_system_calls();
    init_dma_prdt();
    print("Welcome to Johan's Dumb Operating System :)\n");
    enter_user_mode();
}
