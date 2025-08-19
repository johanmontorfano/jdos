#include "devices/raw.h"
#include "devices/vga.h"
#include "devices/ata.h"
#include "kernel/idt.h"
#include "kernel/gdt.h"
#include "kernel/integrated.h"
#include "libc.h"

int main()
{
    clear_screen();
    init_gdt();
    init_idt();
    init_ata();
    start_kernel_shell();
}
