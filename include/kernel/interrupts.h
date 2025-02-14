#ifndef KERNEL_INTERRUPTS
    #define KERNEL_INTERRUPTS
    #define SEG_SELECTORS 0x08
    #define IDT_ENTRIES 256
    #include "drivlib.h"

extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();

extern void irq0();
extern void irq1();
extern void irq2();
extern void irq3();
extern void irq4();
extern void irq5();
extern void irq6();
extern void irq7();
extern void irq8();
extern void irq9();
extern void irq10();
extern void irq11();
extern void irq12();
extern void irq13();
extern void irq14();
extern void irq15();

#define IRQ0 32
#define IRQ1 33
#define IRQ2 34
#define IRQ3 35
#define IRQ4 36
#define IRQ5 37
#define IRQ6 38
#define IRQ7 39
#define IRQ8 40
#define IRQ9 41
#define IRQ10 42
#define IRQ11 43
#define IRQ12 44
#define IRQ13 45
#define IRQ14 46
#define IRQ15 47

typedef struct {
    int ds;
    int edi, esi, ebp, esp, ebx, edx, ecx, eax;
    int int_no, err_code;
    int eip, cs, eflags, useresp, ss;
} t_cpu_reg;

typedef struct {
    unsigned short low_offset;
    unsigned short sel;
    unsigned char always0;
    /// 7       Interrupt is present
    /// 6-5     Privilege level of caller (0..3)
    /// 4       Set to 0 for interrupt gates
    /// 3-0     32-bit interrupt gate
    unsigned char flags;
    unsigned short high_offset;
} __attribute__((packed)) idt_gate_t;

/// asm `lidt` will read this struct to get interrupt handlers.
typedef struct {
    unsigned short limit;
    unsigned int base;
} __attribute__((packed)) idt_reg_t;

typedef void (* isr_t)(t_cpu_reg);

idt_gate_t idt[IDT_ENTRIES];
idt_reg_t idt_reg;

void set_idt(void);
void set_idt_gate(int n, unsigned int handler);
void isr_init(void);
void irq_init(unsigned int tick_speed, t_kb_nl_handler handler);
void irq_handler(t_cpu_reg r);
void reg_int_handler(unsigned char , isr_t handler);

#endif
