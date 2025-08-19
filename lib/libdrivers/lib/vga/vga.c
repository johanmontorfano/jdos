#include "devices/vga.h"
#include "devices/raw.h"
#include "ctypes.h"

// a global VGA buffer
static uint8_t* g_vga_buffer;

// see Intel OpenSource HD Graphics PRM pdf file for following defined data
// for each vga register and its explaination
static uint8_t seq_data[5] = {0x03, 0x01, 0x0F, 0x00, 0x0E};
static uint8_t crtc_data[25] = {
    0x5F, 0x4F, 0x50, 0x82, 0x54, 0x80, 0xBF, 0x1F, 0x00, 0x41, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x9C, 0x0E, 0x8F, 0x28, 0x40, 0x96, 0xB9, 0xA3,
	0xFF
};

static uint8_t gc_data[9] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x05, 0x0F, 0xFF
};

static uint8_t ac_data[21] = {
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B,
	0x0C, 0x0D, 0x0E, 0x0F, 0x41, 0x00, 0x0F, 0x00, 0x00
};

void set_misc()
{
	writeb_port(VGA_MISC_WRITE, 0x63);
}

void set_seq()
{
	// write sequence data to index of 0-4
	for(uint8_t index = 0; index < 5; index++){
		// first set index
		writeb_port(VGA_SEQ_INDEX, index);
		// write data at that index
		writeb_port(VGA_SEQ_DATA, seq_data[index]);
	}
}

void set_crtc()
{
	// write crtc data to index of 0-24
	for(uint8_t index = 0; index < 25; index++){
		writeb_port(VGA_CRTC_INDEX, index);
		writeb_port(VGA_CRTC_DATA, crtc_data[index]);
	}
}

void set_gc()
{
	// write gc data to index of 0-8
	for(uint8_t index = 0; index < 9; index++){
		writeb_port(VGA_GC_INDEX, index);
		writeb_port(VGA_GC_DATA, gc_data[index]);
	}
}

void set_ac()
{
	uint8_t d;
	// write ac data to index of 0-20
	for(uint8_t index = 0; index < 21; index++){
		writeb_port(VGA_AC_INDEX, index);
		writeb_port(VGA_AC_WRITE, ac_data[index]);
	}
	d = readb_port(VGA_INSTAT_READ);
	writeb_port(VGA_AC_INDEX, d | 0x20);
}

void clear_screen()
{
	for(uint32_t index = 0; index < VGA_MAX; index++)
		g_vga_buffer[index] = 0;
}

void clear_color(uint8_t color)
{
	for(uint32_t index = 0; index < VGA_MAX; index++)
		g_vga_buffer[index] = color;
}

void init_vga()
{
	set_misc();
	set_seq();
	set_crtc();
	set_gc();
	set_ac();

	g_vga_buffer = (uint8_t*)VGA_ADDRESS;

	clear_screen();
}

void putpixel(uint16_t x, uint16_t y, uint8_t color)
{
	uint32_t index = 0;
	index = 320 * y + x;
	if(index < VGA_MAX)
		g_vga_buffer[index] = color;
}

void draw_line(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint8_t color)
{
	if (y1 == y2) {
		for (uint16_t i = x1; i <= x2; i++)
			putpixel(i, y1, color);
		return;
	}

	if (x1 == x2) {
		for (uint16_t i = y1; i <= y2; i++)
			putpixel(x1, i, color);
		return;
	}
}

void draw_rect(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t color)
{
	draw_line(x, y, x, y + height, color);
	draw_line(x, y, x + width, y, color);
	draw_line(x + width, y, x + width, y + height, color);
	draw_line(x, y + height, x + width, y + height, color);
}

void fill_rect(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t color)
{
	draw_line(x, y, x, y + height, color);
	draw_line(x, y, x + width, y, color);
	draw_line(x + width, y, x + width, y + height, color);
	draw_line(x, y + height, x + width, y + height, color);
	for (int i = y; i < y + height; i++)
		draw_line(x, i, x + width, i, color);
}
