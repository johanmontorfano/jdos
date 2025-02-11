/// Read a byte from a specific port.
unsigned char readb_port(unsigned short port)
{
    unsigned char result;

    __asm__("in %%dx, %%al" : "=a" (result) : "d" (port));
    return result;
}

void writeb_port(unsigned short port, unsigned char data)
{
    __asm__("out %%al, %%dx" : : "a" (data), "d" (port));
}

/// Read a word from a specific port.
unsigned short readw_port(unsigned short port)
{
    unsigned short result;

    __asm__("in %%dx, %%ax" : "=a" (result) : "d" (port));
    return result;
}

void writew_port(unsigned short port, unsigned short data)
{
    __asm__("out %%ax, %%dx" : : "a" (data), "d" (port));
}
