#include "devices/raw.h"
#include "devices/vga.h"
#include "devices/ata.h"
#include "kernel/idt.h"
#include "kernel/gdt.h"
#include "libc.h"

int main()
{
    clear_screen();
    init_gdt();
    init_idt();
    init_ata();

    const int DRIVE = 0;
    const uint32_t LBA = 0;
    const uint8_t NO_OF_SECTORS = 1;
    char buf[ATA_SECTOR_SIZE] = {0};

    struct example {
        int id;
        char name[32];
    };

    struct example e;
    e.id = 10012;
    s_strcpy(e.name, "Iron Man");

    // write message to drive
    s_strcpy(buf, "Hello World");
    ide_write_sectors(DRIVE, NO_OF_SECTORS, LBA, (uint32_t)buf);

    mem_set(buf, 0, sizeof(buf));
    mem_copy(buf, &e, sizeof(e));
    ide_write_sectors(DRIVE, NO_OF_SECTORS, LBA + 1, (uint32_t)buf);
    p_printf("data written\n");

    // read message from drive
    mem_set(buf, 0, sizeof(buf));
    ide_read_sectors(DRIVE, NO_OF_SECTORS, LBA, (uint32_t)buf);
    p_printf("read data: %s\n", buf);

    mem_set(buf, 0, sizeof(buf));
    ide_read_sectors(DRIVE, NO_OF_SECTORS, LBA + 1, (uint32_t)buf);
    mem_copy(&e, buf, sizeof(e));
    p_printf("id: %d, name: %s\n", e.id, e.name);
}
