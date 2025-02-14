#include "drivlib.h"
#include "clib.h"

/// Checks if the content will overflow from video memory and apply a scroll
/// effect if so.
static int do_scroll(int offset)
{
    int i = 1;
    int cpy = MAX_COLS * 2;
    char *addr1;
    char *addr2;
    char *last;

    if (offset < MAX_ROWS * MAX_COLS * 2)
        return offset;
    while (i < MAX_ROWS) {
        addr1 = ((char *)(VIDEO_BUF + d2off(0, i)));
        addr2 = ((char *)(VIDEO_BUF + d2off(0, i - 1)));
        mem_copy(addr1, addr2, MAX_COLS * 2);
        i++;
    }
    last = ((char *)(d2off(0, MAX_ROWS - 1) + VIDEO_BUF));
    i = 0;
    while (i < MAX_COLS - 2) {
        last[i] = 0;
        i++;
    }
    offset -= 2 * MAX_COLS;
    return offset;
}

/// Transform 2d coordinates to an offset using screen size constants.
int d2off(int col, int row)
{
    return 2 * (row * MAX_COLS + col);
}

int writec(char c, int col, int row)
{
    int offset;

    if (col >= MAX_COLS || row >= MAX_ROWS) {
        VIDEO_BUF[2 * MAX_COLS * MAX_ROWS - 2] = 'E';
        VIDEO_BUF[2 * MAX_COLS * MAX_ROWS - 1] = COLOR_RW;
        return d2off(col, row);
    }
    offset = col >= 0 && row >= 0 ? d2off(col, row) : cursor_get();
    if (c == '\n') {
        row = cursor_get_row(offset);
        offset = d2off(0, row + 1);
    } else {
        VIDEO_BUF[offset] = c;
        VIDEO_BUF[offset + 1] = COLOR_WB;
        offset += 2;
    }
    offset = do_scroll(offset);
    cursor_set(offset);
    return offset;
}

/// To get the position of the cursor:
/// We query the high byte cursor position to the VGA register (0x3d4)
/// -> Data is returned in register 0x3d5.
/// We do the same for the low byte.
/// WARN: The position is offset'd to the reg size (do /2 to revert)
int cursor_get(void)
{
    int position;

    writeb_port(REG_SCREEN_CTRL, 14);
    position = readb_port(REG_SCREEN_DATA) << 8;
    writeb_port(REG_SCREEN_CTRL, 15);
    position += readb_port(REG_SCREEN_DATA);
    return position * 2;
}

int cursor_get_row(int offset)
{
    return offset / (2 * MAX_COLS);
}

int cursor_get_col(int offset)
{
    return (offset - (cursor_get_row(offset) * 2 * MAX_COLS)) / 2;
}

/// Set the cursor position from a offset'd position.
void cursor_set(int pos)
{
    pos /= 2;
    writeb_port(REG_SCREEN_CTRL, 14);
    writeb_port(REG_SCREEN_DATA, (unsigned char)(pos >> 8));
    writeb_port(REG_SCREEN_CTRL, 15);
    writeb_port(REG_SCREEN_DATA, (unsigned char)(pos & 0xff));
}

void clear_screen(void)
{
    // Direct video memory manipulation
    for (int i = 0; i < MAX_ROWS * MAX_COLS * 2; i += 2) {
        VIDEO_BUF[i] = ' ';     // Character
        VIDEO_BUF[i + 1] = COLOR_WB;  // Attribute
    }
    cursor_set(0);  // Reset cursor to top-left
}

void print(char *str)
{
    print_at(str, -1, -1);
}

void print_at(char *str, int row, int col)
{
    int offset;
    int i = 0;

    if (col >= 0 && row >= 0)
        offset = d2off(col, row);
    else {
        offset = cursor_get();
        row = cursor_get_row(offset);
        col = cursor_get_col(offset);
    }
    while (str[i] != 0) {
        offset = writec(str[i], col, row);
        row = cursor_get_row(offset);
        col = cursor_get_col(offset);
        i++;
    }
}

void remove_last_char() {
    int offset = cursor_get() - 2;
    int row = cursor_get_row(offset);
    int col = cursor_get_col(offset);

    writec(' ', col, row);
    cursor_set(offset);
}
