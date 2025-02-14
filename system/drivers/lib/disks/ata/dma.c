#include "drivlib.h"
#include "drivlib/ata.h"

/// PRDT static entry definition
static prdt_t DMA_PRDT __attribute__((aligned(4)));

prdt_t *get_prdt_ref(void)
{
    return &DMA_PRDT;
}

/// WARN: the data buffer is not in words(uint16_t) but in uint32_t, meaning
/// content can be larger. Hence, the size (len) is doubled compared to what
/// it would've been with words.
void dma_lba_write_sector(uint32_t lba_addr, uint32_t *buf, int len)
{
    ata_bsy_wait(ATA_PRIMARY_7);
    DMA_PRDT.base = buf;
    DMA_PRDT.size = len;
    DMA_PRDT.flags = 0x8000;
    write32_port(ATA_DMA_BUS_MASTER_PRDT, (uint32_t)&DMA_PRDT);
    writeb_port(ATA_PRIMARY_2, 1);
    writeb_port(ATA_PRIMARY_3, (uint8_t)lba_addr);
    writeb_port(ATA_PRIMARY_4, (uint8_t)(lba_addr >> 8));
    writeb_port(ATA_PRIMARY_5, (uint8_t)(lba_addr >> 16));
    writeb_port(ATA_PRIMARY_6, 0xE0 | ((lba_addr >> 24) & 0x0F));
    writeb_port(ATA_PRIMARY_7, ATA_DMA_WRITE);
    writeb_port(ATA_DMA_BUS_MASTER_COMMAND, 0x01 | 0x08);
    ata_bmr_wait(ATA_DMA_BUS_MASTER_STATUS);
    writeb_port(ATA_PRIMARY_7, ATA_FLUSH);
    ata_bsy_wait(ATA_PRIMARY_7);
}
