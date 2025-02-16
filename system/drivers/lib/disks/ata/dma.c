#include "drivlib.h"
#include "drivlib/ata.h"
#include "clib.h"

static char *dmawarn = "Some DMA mechanisms are implemented, such as PRD, \
PRDT, DMA WRITE.\nIt is highly not recommended to use DMA in its actual \
implementation because it is incomplete, filled with bugs and breaks \
registers configurations, preventing you from reading/writing to mass \
storage devices unless the OS is restarted.\n";


/// PRDT static entry definition
static prdt_t *DMA_PRDT = (void *)0;

/// If `DMA_PRDT` is not set, it inits it, otherwise it does nothing.
void init_dma_prdt(void)
{
    int i = 0;

    print(dmawarn);
    DMA_PRDT = (prdt_t *)mem_alloc(sizeof(prdt_t) * (ATA_PRD_TABLE_LENGTH + 1));
    while (i < ATA_PRD_TABLE_LENGTH) {
        DMA_PRDT[i].base = 0;
        DMA_PRDT[i].size = 0;
        DMA_PRDT[i].flags = 0;
        i++;
    }
    DMA_PRDT[ATA_PRD_TABLE_LENGTH].flags = 1 << 15;
}

static void debug_prdt(prdt_t *table, int count) {
    for (int i = 0; i < count; i++) {
        print("PRD Entry ");
        write_int(i);
        print(": Buffer Addr = ");
        write_uint(table[i].base);
        print(", Size = ");
        write_uint(table[i].size);
        print(", Flags = ");
        write_uint(table[i].flags);
        print("\n");
    }
}

/// WARN: the data buffer is not in words(uint16_t) but in uint32_t, meaning
/// content can be larger. Hence, the size (len) is doubled compared to what
/// it would've been with words.
void dma_lba_write_sector(uint32_t lba_addr, uint32_t *buf, uint32_t len)
{
    ata_bsy_wait(ATA_PRIMARY_7);
    DMA_PRDT[0].base = (uint32_t)buf;
    DMA_PRDT[0].size = len * sizeof(uint32_t);
    DMA_PRDT[0].flags = 0;
    write32_port(ATA_DMA_BUS_MASTER_PRDT, (uint32_t)DMA_PRDT);
    writeb_port(ATA_DMA_BUS_MASTER_COMMAND, 0x01);
    debug_prdt(DMA_PRDT, ATA_PRD_TABLE_LENGTH);
    writeb_port(ATA_PRIMARY_2, 1);
    writeb_port(ATA_PRIMARY_3, (uint8_t)lba_addr);
    writeb_port(ATA_PRIMARY_4, (uint8_t)(lba_addr >> 8));
    writeb_port(ATA_PRIMARY_5, (uint8_t)(lba_addr >> 16));
    writeb_port(ATA_PRIMARY_6, 0xE0 | ((lba_addr >> 24) & 0x0F));
    writeb_port(ATA_PRIMARY_7, ATA_DMA_WRITE);
    ata_bsy_wait(ATA_PRIMARY_7);
    ata_drq_wait(ATA_PRIMARY_7);
    writeb_port(ATA_DMA_BUS_MASTER_COMMAND, 0x09);
    ata_bmr_wait(ATA_DMA_BUS_MASTER_STATUS);
    writeb_port(ATA_DMA_BUS_MASTER_COMMAND, 0x00);
    ata_bsy_wait(ATA_PRIMARY_7);
    writeb_port(ATA_PRIMARY_7, ATA_FLUSH);
    ata_bsy_wait(ATA_PRIMARY_7);
}
