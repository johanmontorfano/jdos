#include "devices/ata.h"
#include "kernel/buffers.h"
#include "kernel/integrated.h"
#include "devices/raw.h"
#include "ctypes.h"
#include "libc.h"

void nona() {
    uint8_t run = 1;
    uint8_t mode = 2;
    uint32_t prev_stdin_size = stdin_size;

    stdin_flush();
    while (run) {
        if (stdin_size != prev_stdin_size && mode == 1) {
            clear_screen();
            write(stdin, stdin_size);
            prev_stdin_size = stdin_size;
        }
        if (kb_esc_pressed || mode == 2) {
            clear_screen();
            p_printf("nona v0\n");
            p_printf("the dumb text editor\n");
            p_printf("   to come back here, press <esc>\n");
            p_printf("   to start writing, press c + <enter>\n");
            p_printf("   to save to a file, write s + <enter>\n");
            p_printf("   to exit, press q + <enter>\n");

            char *choice = getinputsilent();

            if (choice[0] == 'c') {
                mode = 1;
                stdin_size = prev_stdin_size | 2;
            } else if (choice[0] == 's') {
                p_printf("\n");
                p_printf("woah, you want to save your data to a raw thing!\n");
                p_printf("what's the file name> ");
                
                char *fname = getinput();
                int fname_sector_size = s_strlen(fname) / ATA_SECTOR_SIZE + 1;

                p_printf("%s:%d %d:%d\n", fname, fname_sector_size, stdin_size, stdin_size / ATA_SECTOR_SIZE);

                ide_write_sectors(0, fname_sector_size, 0, (uint32_t)fname);
                ide_write_sectors(0, stdin_size / ATA_SECTOR_SIZE + 1, fname_sector_size, (uint32_t)stdin);
                p_printf("=== saved ===");
            }
            else if (choice[0] == 'q')
                run = 0;
        }

    }
}

void start_kernel_shell() {
    uint8_t run = 1;
    char *line;

    keyboard_init();
    p_printf("Welcome to Johan's Dumb Operating System!\n");
    while (run) {
        write("> ", 2);
        line = getinput();
        if (!s_strcmp(line, "help")) {
            p_printf("here is some help!\n");
            p_printf(" - help, you know what it does\n");
            p_printf(" - nona, opens a text editor\n");
            p_printf(" - clear, clears the screen\n");
            p_printf(" - exit, halts the kernel\n");
        } else if (!s_strcmp(line, "nona"))
            nona();
        else if (!s_strcmp(line, "exit"))
            run = 0;
        else if (!s_strcmp(line, "clear"))
            clear_screen();
    }
}
