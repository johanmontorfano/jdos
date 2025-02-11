#include "drivlib.h"
#include "interrupts.h"
#include "stdlib.h"

static t_kb_nl_handler nl_handler;
char key_buffer[512];
int alloc_size = 0;
int kb_layout = KB_LAYOUT_QWERTY;

/// WARN: scancode - 1 may not be fitted for all keyboards/keyboard layouts
static void keycback(t_cpu_reg regs)
{
    char print_buf[2] = { 0, 0 };
    unsigned char scancode = readb_port(0x60);
    char vk_char = get_keyboard_layout(kb_layout)[scancode - 1];

    if (scancode == KB_BACKSPACE && alloc_size > 0) {
        alloc_size -= 1;
        key_buffer[alloc_size] = 0;
        remove_last_char();
    } else if (scancode == KB_ENTER) {
        print("\n");
        nl_handler(key_buffer);
        alloc_size = 0;
        key_buffer[0] = 0;
    } else if (scancode < 85 && c_isalphanum(vk_char)) {
        print_buf[0] = vk_char;
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

void update_kb_layout(int code)
{
    kb_layout = code;
}
