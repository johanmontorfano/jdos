#ifndef KERNEL_DEVICE_VGA
    #define KERNEL_DEVICE_VGA
	#define VGA_ADDRESS 0xA0000
    #define VGA_MAX 0xF9FF
	#define VGA_MAX_WIDTH 320
    #define VGA_MAX_HEIGHT 200
    #define	VGA_AC_INDEX 0x3C0
	#define	VGA_AC_READ 0x3C1
    #define	VGA_AC_WRITE 0x3C0
	#define	VGA_MISC_READ 0x3CC
	#define	VGA_MISC_WRITE 0x3C2
	#define VGA_SEQ_INDEX 0x3C4
	#define VGA_SEQ_DATA 0x3C5
	#define	VGA_DAC_READ_INDEX 0x3C7
	#define	VGA_DAC_WRITE_INDEX 0x3C8
	#define	VGA_DAC_DATA 0x3C9
	#define VGA_GC_INDEX 0x3CE
	#define VGA_GC_DATA 0x3CF
	#define VGA_CRTC_INDEX 0x3D4
	#define VGA_CRTC_DATA 0x3D5
	#define	VGA_INSTAT_READ 0x3DA
    #define BITMAP_SIZE 8
    #include "ctypes.h"

enum vga_color {
  BLACK,
  BLUE,
  GREEN,
  CYAN,
  RED,
  MAGENTA,
  BROWN,
  GREY,
  DARK_GREY,
  BRIGHT_BLUE,
  BRIGHT_GREEN,
  BRIGHT_CYAN,
  BRIGHT_RED,
  BRIGHT_MAGENTA,
  YELLOW,
  WHITE,
};

void init_vga();
void clear_screen();
void clear_color(uint8_t color);
void putpixel(uint16_t x, uint16_t y, uint8_t color);
void draw_line(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint8_t color);
void draw_rect(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t color);
void fill_rect(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t color);
void draw_char(uint16_t x, uint16_t y, uint8_t color, char ch);
void draw_string(uint16_t x, uint16_t y, uint8_t color, char *str);

#endif
