#include "devices/raw.h"
#include "devices/ata.h"
#include "devices/vga.h"
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
    init_vga();
    fill_rect(0, 0, VGA_MAX_WIDTH - 1, VGA_MAX_HEIGHT - 1, BLUE);
    draw_string(30, 30, WHITE, "JDOS V0");
    draw_string(30, 40, WHITE, "WELCOME!");
}
