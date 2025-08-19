#include "devices/raw.h"
#include "kernel/buffers.h"
#include "kernel/interrupts.h"
#include "libc.h"

int kb_layout = KB_LAYOUT_AZERTY;
int kb_shift_pressed = 0;
int kb_esc_pressed = 0;
// determines if received characters should be printed
int kb_explicit_mode = 0;

/// WARN: scancode - 1 may not be fitted for all keyboards/keyboard layouts
static void keycback(t_cpu_reg regs)
{
    char print_buf[2] = { 0, 0 };
    unsigned char scancode = readb_port(0x60);
    char vk_char = get_keyboard_layout(kb_layout)[scancode - 1];

    kb_esc_pressed = scancode == 129;
    if (scancode == 57)
        vk_char = ' ';
    if (scancode == 42)
        kb_shift_pressed = !kb_shift_pressed;
    if (scancode == KB_BACKSPACE && stdin_size > 0) {
        stdin_size -= 1;
        if (kb_explicit_mode)
            remove_last_char();
    } else if (scancode == KB_ENTER) {
        stdin_write('\n');
        if (kb_explicit_mode)
            print("\n");
    }
    else if (scancode < 85 && c_isprintable(vk_char)) {
        if (c_isalphalow(vk_char) && kb_shift_pressed)
            vk_char -= 32;
        print_buf[0] = vk_char;
        stdin_write(print_buf[0]);
        if (kb_explicit_mode)
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
