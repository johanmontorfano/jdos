#include "drivlib.h"
#include "interrupts.h"

static t_kb_nl_handler nl_handler;
char key_buffer[512];
int alloc_size = 0;
int kb_layout = KB_LAYOUT_QWERTY;

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
    } else {
        print_buf[0] = get_keyboard_layout(kb_layout)[scancode - 1];
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
