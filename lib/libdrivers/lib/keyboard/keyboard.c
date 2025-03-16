#include "drivlib.h"
#include "kernel/buffers.h"
#include "kernel/interrupts.h"
#include "libc.h"

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
    if (scancode == KB_BACKSPACE && stdin_size > 0) {
        stdin_size -= 1;
    } else if (scancode == KB_ENTER) {
        stdin_write('\n');
        if (ECHO_KEYBOARD)
            print("\n");
    }
    else if (scancode < 85 && c_isprintable(vk_char)) {
        if (c_isalphalow(vk_char) && kb_shift_pressed)
            vk_char -= 32;
        print_buf[0] = vk_char;
        stdin_write(print_buf[0]);
        if (ECHO_KEYBOARD)
            print(print_buf);
    }
}

void keyboard_init(void)
{
    reg_int_handler(IRQ1, keycback);
}

void update_kb_layout(int code)
{
    kb_layout = code;
}
