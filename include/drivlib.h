#ifndef KERNEL_DRIV
    #define KERNEL_DRIV
    #define VIDEO_HEX 0xb8000
    #define VIDEO_BUF ((volatile char *)0xb8000)
    #define MAX_ROWS 25
    #define MAX_COLS 80
    #define COLOR_WB 0x0f
    #define COLOR_RW 0xf4
    #define KB_BACKSPACE 0x0E
    #define KB_ENTER 0x1C
    #define KB_VK_SHIFT 0xF2
    #define KB_VK_CAPSL 0xF3
    #define KB_LAYOUT_AZERTY 0
    #define KB_LAYOUT_QWERTY 1
    #define REG_SCREEN_CTRL 0x3d4
    #define REG_SCREEN_DATA 0x3d5
    #include "ctypes.h"

int writec(char c, int col, int row);
int d2off(int col, int row);
int cursor_get_row(int offset);
int cursor_get_col(int offset);
int cursor_get(void);
const char *get_keyboard_layout(int code);
uint8_t readb_port(uint16_t port);
uint16_t readw_port(uint16_t port);
uint32_t read32_port(uint16_t port);
void writeb_port(uint16_t port, uint8_t data);
void writew_port(uint16_t port, uint16_t data);
void write32_port(uint16_t port, uint32_t data);
void clear_screen(void);
void print(char *str);
void print_at(char *str, int row, int col);
void cursor_set(int pos);
void keyboard_init(void);
void remove_last_char(void);
void update_kb_layout(int code);

#endif
