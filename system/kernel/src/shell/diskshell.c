#include "clib.h"
#include "drivlib.h"
#include "drivlib/ata.h"
#include "kernel/shell.h"

static void test_overwrite(int secs)
{
    uint16_t buf[256];
    int s = 0;
    int i = 0;

    while (i < 255) {
        buf[i] = 0x0F0F;
        i++;
    }
    while (s < secs) {
        pio_lba_write_sector(s, buf, 256);
        s++;
    }
}

static void test_overread(int secs)
{
    uint16_t *buf;
    int s = 0;
    int i = 0;

    while (s < secs) {
        buf = pio_lba_read_sector(s);
        i = 0;
        while (i < 128) {
            write_uint(buf[i]);
            print(" ");
            i++;
        }
        s++;
    }
}

static void test_disk_io(void)
{
    uint16_t buffer[6] = { 110, 12, 15, 14, 8493, 234 };
    uint16_t *read_data;

    pio_lba_write_sector(0, buffer, 6);
}

static void print_udma_entry(int type, int ok)
{
    print("UDMA ");
    write_int(type);
    print(": ");
    if (ok) {
        print("supported ");
        write_int(ok);
    } else {
        print("unsupported ");
        write_int(ok);
    }
    print("\n");
}

static void test_disk_info(void)
{
    t_disk_info *info = get_disk_info();

    print("Disk exist: ");
    write_int(info->is_found);
    print("\nMaster disk: ");
    write_int(info->is_master);
    print("\nATA disk: ");
    write_int(info->is_ata);
    print("\nLBA28: ");
    write_int(info->support_lba28);
    print("\nLBA28 Addr Quantity: ");
    write_uint(info->lba28_addr);
    print("\nLBA48: ");
    write_int(info->support_lba48);
    print("\nLBA48 Addr Quantity: ");
    write_uint(info->lba48_addr);
    print("\nActive UDMA mode: ");
    write_int(info->active_udma_mode);
    print("\n");
    print_udma_entry(1, info->support_udma1);
    print_udma_entry(2, info->support_udma2);
    print_udma_entry(3, info->support_udma3);
    print_udma_entry(4, info->support_udma4);
    print_udma_entry(5, info->support_udma5);
    print_udma_entry(6, info->support_udma6);
    print_udma_entry(7, info->support_udma7);
    print_udma_entry(8, info->support_udma8);
}

static void diskshell_online(char *str)
{
    char **args = argparse(str);

    if (!s_strcmp(args[0], "TEST"))
        test_disk_io();
    if (!s_strcmp(args[0], "INFO"))
        test_disk_info();
    if (!s_strcmp(args[0], "OVERWRITE"))
        test_overwrite(256);
    if (!s_strcmp(args[0], "OVERREAD"))
        test_overread(1);
    if (!s_strcmp(args[0], "EXIT")) {
        print("\n");
        print("> ");
        return read_keyboard(on_line);
    }
    print("DISKSHELL> ");
}

void diskshell(void)
{
    read_keyboard(diskshell_online);
    print_program_handle(DISKSHELL_NAME, DISKSHELL_VER);
    print("DISKSHELL> ");
}
