/// Source:
///     https://wiki.osdev.org/ATA_PIO_Mode#IDENTIFY_command

#include "libc.h"
#include "drivlib.h"
#include "drivlib/ata.h"

static uint8_t get_udma_active_mode(uint16_t udma_word)
{
    int i = 7;

    while (i >= 0) {
        if (uint16bitst(udma_word, i))
            return i + 1;
        i--;
    }
    return 0;
}

/// Get basic ATA disk info.
/// TODO: Add support for ATA kind detection.
t_disk_info *prepare_disk()
{
    t_disk_info *info = (t_disk_info *)mem_alloc(sizeof(t_disk_info));

    info->is_master = 1;
    info->is_found = 0;
    info->is_ata = 0;
    writeb_port(ATA_PRIMARY_6, 0xA0);
    writeb_port(ATA_PRIMARY_2, 0);
    writeb_port(ATA_PRIMARY_3, 0);
    writeb_port(ATA_PRIMARY_4, 0);
    writeb_port(ATA_PRIMARY_5, 0);
    writeb_port(ATA_PRIMARY_7, 0xEC);
    if (readb_port(ATA_PRIMARY_7) == 0)
        return info;
    info->is_found = 1;
    ata_bsy_wait(ATA_PRIMARY_7);
    if (readb_port(ATA_PRIMARY_4) || readb_port(ATA_PRIMARY_5))
        return info;
    info->is_ata = 1;
    ata_drq_err_wait(ATA_PRIMARY_7);
    return info;
}

/// Prepare the disk and get info from the IDENTIFY command.
t_disk_info *get_disk_info()
{
    t_disk_info *disk = prepare_disk();
    uint16_t wo[256];
    uint32_t i = 0;

    if (!disk->is_found || !disk->is_ata)
        return disk;
    while (i < 256) {
        wo[i] = readw_port(ATA_PRIMARY_7);
        i++;
    }
    disk->support_lba48 = wo[83] & (1 << 9);
    disk->lba48_addr = (uint64_t)wo[100] + wo[101] + wo[102] + wo[103];
    disk->support_udma1 = uint16bitst(wo[88], 15);
    disk->support_udma2 = uint16bitst(wo[88], 14);
    disk->support_udma3 = uint16bitst(wo[88], 13);
    disk->support_udma4 = uint16bitst(wo[88], 12);
    disk->support_udma5 = uint16bitst(wo[88], 11);
    disk->support_udma6 = uint16bitst(wo[88], 10);
    disk->support_udma7 = uint16bitst(wo[88], 9);
    disk->support_udma8 = uint16bitst(wo[88], 8);
    disk->active_udma_mode = get_udma_active_mode(wo[88]);
    disk->udma_up_2_ok = wo[93] & (1 << 10);
    disk->lba28_addr = (uint32_t)wo[60] + wo[61];
    disk->support_lba28 = disk->lba28_addr > 0;
    return disk;
}
