#include "ctypes.h"
#include "drivlib.h"

/// Read a byte from a specific port.
uint8_t readb_port(uint16_t port)
{
    unsigned char result;

    __asm__("inb %%dx, %%al" : "=a" (result) : "d" (port));
    return result;
}

void writeb_port(uint16_t port, uint8_t data)
{
    __asm__("outb %%al, %%dx" : : "a" (data), "d" (port));
}

/// Read a word from a specific port.
unsigned short readw_port(uint16_t port)
{
    unsigned short result;

    __asm__("inw %%dx, %%ax" : "=a" (result) : "d" (port));
    return result;
}

void writew_port(uint16_t port, uint16_t data)
{
    __asm__("outw %%ax, %%dx" : : "a" (data), "d" (port));
}
