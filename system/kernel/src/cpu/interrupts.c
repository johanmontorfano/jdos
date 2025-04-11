#include "kernel/interrupts.h"
#include "kernel/cpu.h"
#include "drivlib.h"
#include "ctypes.h"
#include "libc.h"

isr_t int_handlers[256];
uint8_t previous_int = 255;
char *exception_msg[] = {
    "Division By Zero",
    "Debug",
    "Non Maskable Interrupt",
    "Breakpoint",
    "Into Detected Overflow",
    "Out of Bounds",
    "Invalid Opcode",
    "No Coprocessor",
    "Double Fault",
    "Coprocessor Segment Overrun",
    "Bad TSS",
    "Segment Not Present",
    "Stack Fault",
    "General Protection Fault",
    "Page Fault",
    "Unknown Interrupt",
    "Coprocessor Fault",
    "Alignment Check",
    "Machine Check",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved"
};

void set_idt(void)
{
    idt_reg.base = (unsigned int)&idt;
    idt_reg.limit = IDT_ENTRIES * sizeof(idt_gate_t) - 1;
    __asm__ __volatile__("lidtl (%0)" : : "r" (&idt_reg));
}

void set_idt_gate(int n, unsigned int handler)
{
    idt[n].low_offset = (unsigned short)(handler & 0xFFFF); //low16
    idt[n].sel = SEG_SELECTORS;
    idt[n].always0 = 0;
    idt[n].flags = 0x8E;
    idt[n].high_offset = (unsigned short)((handler >> 16) & 0xFFFF);
}

void isr_init(void)
{
    set_idt_gate(0, (unsigned int)isr0);
    set_idt_gate(1, (unsigned int)isr1);
    set_idt_gate(2, (unsigned int)isr2);
    set_idt_gate(3, (unsigned int)isr3);
    set_idt_gate(4, (unsigned int)isr4);
    set_idt_gate(5, (unsigned int)isr5);
    set_idt_gate(6, (unsigned int)isr6);
    set_idt_gate(7, (unsigned int)isr7);
    set_idt_gate(8, (unsigned int)isr8);
    set_idt_gate(9, (unsigned int)isr9);
    set_idt_gate(10, (unsigned int)isr10);
    set_idt_gate(11, (unsigned int)isr11);
    set_idt_gate(12, (unsigned int)isr12);
    set_idt_gate(13, (unsigned int)isr13);
    set_idt_gate(14, (unsigned int)isr14);
    set_idt_gate(15, (unsigned int)isr15);
    set_idt_gate(16, (unsigned int)isr16);
    set_idt_gate(17, (unsigned int)isr17);
    set_idt_gate(18, (unsigned int)isr18);
    set_idt_gate(19, (unsigned int)isr19);
    set_idt_gate(20, (unsigned int)isr20);
    set_idt_gate(21, (unsigned int)isr21);
    set_idt_gate(22, (unsigned int)isr22);
    set_idt_gate(23, (unsigned int)isr23);
    set_idt_gate(24, (unsigned int)isr24);
    set_idt_gate(25, (unsigned int)isr25);
    set_idt_gate(26, (unsigned int)isr26);
    set_idt_gate(27, (unsigned int)isr27);
    set_idt_gate(28, (unsigned int)isr28);
    set_idt_gate(29, (unsigned int)isr29);
    set_idt_gate(30, (unsigned int)isr30);
    set_idt_gate(31, (unsigned int)isr31);

    // PIC remap
    writeb_port(0x20, 0x11);
    writeb_port(0xA0, 0x11);
    writeb_port(0x21, 0x20);
    writeb_port(0xA1, 0x28);
    writeb_port(0x21, 0x04);
    writeb_port(0xA1, 0x02);
    writeb_port(0x21, 0x01);
    writeb_port(0xA1, 0x01);
    writeb_port(0x21, 0x0);
    writeb_port(0xA1, 0x0);

    // IRQ init
    set_idt_gate(32, (unsigned int)irq0);
    set_idt_gate(33, (unsigned int)irq1);
    set_idt_gate(34, (unsigned int)irq2);
    set_idt_gate(35, (unsigned int)irq3);
    set_idt_gate(36, (unsigned int)irq4);
    set_idt_gate(37, (unsigned int)irq5);
    set_idt_gate(38, (unsigned int)irq6);
    set_idt_gate(39, (unsigned int)irq7);
    set_idt_gate(40, (unsigned int)irq8);
    set_idt_gate(41, (unsigned int)irq9);
    set_idt_gate(42, (unsigned int)irq10);
    set_idt_gate(43, (unsigned int)irq11);
    set_idt_gate(44, (unsigned int)irq12);
    set_idt_gate(45, (unsigned int)irq13);
    set_idt_gate(46, (unsigned int)irq14);
    set_idt_gate(47, (unsigned int)irq15);

    set_idt();
}

/// Inits: timer + keyboard
void irq_init(unsigned int tick_speed)
{
    asm volatile("sti");
    timer_init(tick_speed);
    keyboard_init();
}

void isr_handler(t_cpu_reg r)
{
    char s[3];

    if (previous_int == r.int_no)
        return;
    previous_int = r.int_no;
    print("!! ");
    write_int(r.int_no);
    print(" -> ");
    print(exception_msg[r.int_no]);
    print("\n");
}

void reg_int_handler(unsigned char intr, isr_t handler)
{
    int_handlers[intr] = handler;
}

/// Handle the interrupt and notify the PIC it can send interrupts again.
void irq_handler(t_cpu_reg r)
{
    isr_t handler;

    if (r.int_no >= 40)
        writeb_port(0xA0, 0x20);
    writeb_port(0x20, 0x20);
    if (int_handlers[r.int_no] != 0) {
        handler = int_handlers[r.int_no];
        handler(r);
    }
}
