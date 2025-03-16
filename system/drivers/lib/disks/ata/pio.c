#include "libc.h"
#include "ctypes.h"
#include "drivlib.h"
#include "drivlib/ata.h"

void pio_lba_write_sector(uint32_t lba_addr, uint16_t *buffer, int len)
{
    int i = 0;

    ata_bsy_wait(ATA_PRIMARY_7);
    writeb_port(ATA_PRIMARY_2, 1);
    writeb_port(ATA_PRIMARY_3, (uint8_t)lba_addr);
    writeb_port(ATA_PRIMARY_4, (uint8_t)(lba_addr >> 8));
    writeb_port(ATA_PRIMARY_5, (uint8_t)(lba_addr >> 16));
    writeb_port(ATA_PRIMARY_6, 0xE0 | ((lba_addr >> 24) & 0x0F));
    writeb_port(ATA_PRIMARY_7, ATA_PIO_WRITE);
    ata_drq_wait(ATA_PRIMARY_7);
    while (i < 256) {
        writew_port(ATA_PRIMARY_0, i < len ? buffer[i] : 0);
        readb_port(ATA_PRIMARY_7);
        i++;
    }
    writeb_port(ATA_PRIMARY_7, ATA_FLUSH);
    ata_bsy_wait(ATA_PRIMARY_7);
}

uint16_t *pio_lba_read_sector(uint32_t lba_addr)
{
    int i = 0;
    uint16_t *buf = (uint16_t *)mem_alloc(sizeof(uint16_t) * 256);

    ata_bsy_wait(ATA_PRIMARY_7);
    writeb_port(ATA_PRIMARY_2, 1);
    writeb_port(ATA_PRIMARY_3, (uint8_t)lba_addr);
    writeb_port(ATA_PRIMARY_4, (uint8_t)(lba_addr >> 8));
    writeb_port(ATA_PRIMARY_5, (uint8_t)(lba_addr >> 16));
    writeb_port(ATA_PRIMARY_6, 0xE0 | ((lba_addr >> 24) & 0x0F));
    writeb_port(ATA_PRIMARY_7, ATA_PIO_READ);
    ata_drq_wait(ATA_PRIMARY_7);
    while (i < 256) {
        buf[i] = readw_port(ATA_PRIMARY_0);
        i++;
    }
    ata_bsy_wait(ATA_PRIMARY_7);
    return buf;
}
