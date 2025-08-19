// Definitions for the 8259 Programmable Interrupts Controller
// https://wiki.osdev.org/8259_PIC

#ifndef KERNEL_PIC_8259
    #define KERNEL_PIC_8259
    #include "ctypes.h"

#define PIC1            0x20        // IO base address for master PIC
#define PIC2            0xA0        // IO base address for slave PIC
#define PIC1_COMMAND    PIC1
#define PIC1_DATA       (PIC1+1)    // master data
#define PIC2_COMMAND    PIC2
#define PIC2_DATA       (PIC2+1)    // slave data

#define PIC_EOI         0x20        // end of interrupt

#define ICW1            0x11        // interrupt word PIC for init
#define ICW4_8086       0x01        // 8086/88 mode


void pic8259_init();
void pic8259_eoi(uint8_t irq);

#endif
