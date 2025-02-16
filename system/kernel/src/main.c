#include "drivlib.h"
#include "drivlib/ata.h"
#include "kernel/interrupts.h"
#include "kernel/shell.h"

int main()
{
    unsigned char *line;

    print("kernel: init interruptions\n");
    isr_init();
    irq_init(50, &on_line);
    print("kernel: init DMA PRD table\n");
    init_dma_prdt();
    print("kernel: ok\n");
    print("shell: ok\n");
    print("Type HELP to get available commands...\n");
    print("> ");
}
