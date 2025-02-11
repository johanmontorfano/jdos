#include "drivlib.h"
#include "interrupts.h"
#include "shell.h"

int main()
{
    unsigned char *line;

    print("kernel: init interruptions\n");
    isr_init();
    irq_init(50, &on_line);
    print("kernel: ok\n");
    print("shell: ok\n");
    clear_screen();
    print("Type EXIT to halt the system, SHELL to get shell's version, ...\n");
    print("> ");
}
