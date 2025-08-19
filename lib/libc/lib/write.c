#include "libc.h"
#include "devices/raw.h"

void write(char *str, int n)
{
    int i = 0;
    int off = cursor_get();

    while (i < n) {
        off = writec(str[i], cursor_get_col(off), cursor_get_row(off));
        i++;
    }
}

void write_char(char c)
{
    write(&c, 1);
}

void write_int(int nb)
{
    char c;

    if (nb < 0) {
        print("-");
        nb *= -1;
    }
    if (nb < 10) {
        c = nb + 48;
        write(&c, 1);
    }
    else {
        write_int(nb / 10);
        write_int(nb % 10);
    }
}

void write_uint(unsigned int nb)
{
    char c;

    if (nb < 0) {
        print("-");
        nb *= -1;
    }
    if (nb < 10) {
        c = nb + 48;
        write(&c, 1);
    }
    else {
        write_uint(nb / 10);
        write_uint(nb % 10);
    }
}

void write_hex(unsigned int nb)
{
    int i = 0;
    char base[16] = "0123456789abcdef";

    if (nb < 16)
        write(&base[nb], 1);
    else {
        write_hex(nb / 16);
        write_hex(nb % 16);
    }
}
