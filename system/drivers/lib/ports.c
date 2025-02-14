#include "clib.h"
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

/// Read a 32-bit unsigned int from a specific port
uint32_t read32_port(uint16_t port)
{
    uint16_t low = readw_port(port);
    uint16_t high = readw_port(port);

    return ui16c32(high, low);
}

void write32_port(uint16_t port, uint32_t data)
{
    writew_port(port, data);
    data = data >> 16;
    writew_port(port, data);
}
