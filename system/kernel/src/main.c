#include "drivlib.h"
#include "drivlib/ata.h"
#include "kernel/interrupts.h"
#include "kernel/shell.h"

int main()
{
    clear_screen();
    print("kernel: initialization\n");
    isr_init();
    irq_init(50);
    init_dma_prdt();
    print("Welcome to Johan's Dumb Operating System :)\n");
    print("> ");
}
