#include "drivlib.h"
#include "interrupts.h"

static t_kb_nl_handler nl_handler;
/// AZERTY-based
static const char ascii_chars[] = {
    'A', 'Z', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', // 0x10 .. 0x1B
    '?', '?', '?', '?',
    'Q', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', 'M', // 0x1E .. 0x27
    '?', '?', '?', '?',
    'W', 'X', 'C', 'V', 'B', 'N', '?', '.', '/'      // 0x2C .. 0x35
};
unsigned int alloc_size = 0;
char key_buffer[512];

static void keycback(t_cpu_reg regs)
{
    char print_buf[2] = { 0, 0 };
    unsigned char scancode = readb_port(0x60);

    if (scancode == KB_BACKSPACE && alloc_size > 0) {
        alloc_size -= 1;
        key_buffer[alloc_size] = 0;
        remove_last_char();
    } else if (scancode == KB_ENTER) {
        print("\n");
        nl_handler(key_buffer);
        alloc_size = 0;
        key_buffer[0] = 0;
    } else if (scancode - 0x10 >= 0 && scancode - 0x10 <= 0x25) {
        print_buf[0] = ascii_chars[scancode - 0x10];
        print(print_buf);
        key_buffer[alloc_size] = print_buf[0];
        alloc_size += 1;
        key_buffer[alloc_size] = 0;
    }
}

void keyboard_init(t_kb_nl_handler handler)
{
    nl_handler = handler;
    reg_int_handler(IRQ1, keycback);
}
