#include "kernel/interrupts.h"
#include "devices/pic_8259.h"
#include "devices/raw.h"
#include "ctypes.h"

void pic8259_init() {
    uint8_t a1, a2;

    // save mask registers
    a1 = readb_port(PIC1_DATA);
    a2 = readb_port(PIC2_DATA);

    // send commands to pic to initialize both master & slave
    writeb_port(PIC1_COMMAND, ICW1);
    writeb_port(PIC2_COMMAND, ICW1);

    // map vector offset of all default IRQ's from 0x20 to 0x27 in master(ICW2)
    writeb_port(PIC1_DATA, 0x20);
    // map vector offset of all default IRQ's from 0x28 to 0x2F in slave(ICW2)
    writeb_port(PIC2_DATA, 0x28);

    // ICW3: tell master PIC that there is a slave PIC at IRQ2 (0000 0100)
    writeb_port(PIC1_DATA, 4);
    // ICW3: tell slave PIC its cascade identity (0000 0010)
    writeb_port(PIC2_DATA, 2);

    // ICW4, set x86 mode
    writeb_port(PIC1_DATA, ICW4_8086);
    writeb_port(PIC2_DATA, ICW4_8086);

    // restore the mask registers
    writeb_port(PIC1_DATA, a1);
    writeb_port(PIC2_DATA, a2);
}

// EOI = End Of Input
void pic8259_eoi(uint8_t irq) {
    if(irq >= 0x28)
        writeb_port(PIC2, PIC_EOI);
    writeb_port(PIC1, PIC_EOI);
}
