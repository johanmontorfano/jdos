#include "drivlib.h"
#include "kernel/interrupts.h"
#include "libc.h"

static t_kb_nl_handler nl_handler;
char key_buffer[512];
int alloc_size = 0;
int kb_layout = KB_LAYOUT_AZERTY;
int kb_shift_pressed = 0;

/// WARN: scancode - 1 may not be fitted for all keyboards/keyboard layouts
static void keycback(t_cpu_reg regs)
{
    char print_buf[2] = { 0, 0 };
    unsigned char scancode = readb_port(0x60);
    char vk_char = get_keyboard_layout(kb_layout)[scancode - 1];

    if (scancode == 57)
        vk_char = ' ';
    if (scancode == 42)
        kb_shift_pressed = !kb_shift_pressed;
    if (scancode == KB_BACKSPACE && alloc_size > 0) {
        alloc_size -= 1;
        key_buffer[alloc_size] = 0;
        remove_last_char();
    } else if (scancode == KB_ENTER) {
        print("\n");
        nl_handler(key_buffer);
        alloc_size = 0;
        key_buffer[0] = 0;
    } else if (scancode < 85 && c_isprintable(vk_char)) {
        if (c_isalphalow(vk_char) && kb_shift_pressed)
            vk_char -= 32;
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

/// Set a new handler for the keyboard.
void read_keyboard(t_kb_nl_handler handler)
{
    nl_handler = handler;
}

void update_kb_layout(int code)
{
    kb_layout = code;
}
