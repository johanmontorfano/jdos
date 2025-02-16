#ifndef KERNEL_DRIV_ATA
    #define KERNEL_DRIV_ATA
    // We consider that data returned/expected by all those registers is
    // of type uint8_t.
    // Rows with a '*' means LBA28 = uint8_t, LBA48 = uint16_t
    // Rows with a '^' means LBA28/LBA48 = uint16_t
    #include <stdint.h>
#define ATA_PRIMARY_0 0x1F0                 // R/W PIO bytes            ^
    #define ATA_PRIMARY_1 0x1F1                 // R: Error                 *
                                                // W: Features              *
    #define ATA_PRIMARY_2 0x1F2                 // SectorCount              *
    #define ATA_PRIMARY_3 0x1F3                 // LBAlo (SectorNb)         *
    #define ATA_PRIMARY_4 0x1F4                 // LBAmid (CylinderLow)     *
    #define ATA_PRIMARY_5 0x1F5                 // LBAhi (CylinderHi)       *
    /// The Drive/Head Register (and the Drive/Head Selected Register), are
    /// using uint8_t formatted as:
    /// bits 0-3:   CHS(bits 0-3 of the head) LBA(bits 24-27 of the blk nb)
    /// bit    4:   Drive number
    /// bit    5:   Always set to 1
    /// bit    6:   0 = CHS addressing, 1 = LBA addressing
    /// bit    7:   Always set to 1
    #define ATA_PRIMARY_6 0x1F6                 // Drive/Head Register
    /// The Status Register (and the Alternate Status Register), are using
    /// uint8_t formatted as:
    /// bit    0:   Error, new command clears it
    /// bit    1:   Index, always set to 0
    /// bit    2:   Corrected Data, always set to 0
    /// bit    3:   DRQ, 1 = Drive is ready/has PIO data to transfer
    /// bit    4:   Overlapped Mode Service Req (?????)
    /// bit    5:   Drive Fault Error
    /// bit    6:   0 = Drive spun down, after an error
    /// bit    7:   If set, drive is busy
    #define ATA_PRIMARY_7 0x1F7                 // R: Status
                                                // W: Command
    /// The Device Control Register (W) is using uint8_t formatted as:
    /// bit    0:   Always set to 0
    /// bit    1:   If set, device will not send interrupts anymore
    /// bit    2:   If set, ATA drives undergoes a software reset
    /// bits 3-6:   Reserved
    /// bit    7:   If set, will allow to read the high order byte of the last
    ///             LBA48 address.
    #define ATA_PRIMARY_CONTROL_1 0x3F6         // R: Alternate Status
                                                //    Does not affect int
                                                // W: Device Control
    /// Drive Address Register
    /// bit    0:   Cleared when drive 0 selected
    /// bit    1:   Cleared when drive 1 selected
    /// bits 2-5:   ????
    /// bit    6:   Write gate, low voltage when writing
    /// bit    7:   Reserved for compatibility with floppy disks
    #define ATA_PRIMARY_CONTROL_2 0x3F7         // R: Drive Address
    #define ATA_PRIMARY_IRQ 14

    #define ATA_SECONDARY_0 0x170
    #define ATA_SECONDARY_1 0x171
    #define ATA_SECONDARY_2 0x172
    #define ATA_SECONDARY_3 0x173
    #define ATA_SECONDARY_4 0x174
    #define ATA_SECONDARY_5 0x175
    #define ATA_SECONDARY_6 0x176
    #define ATA_SECONDARY_7 0x177
    #define ATA_SECONDARY_CONTROL_1 0x376
    #define ATA_SECONDARY_CONTROL_2 0x377
    #define ATA_SECONDARY_IRQ 15

    // ATA Error register kinds
    #define ATA_ERR_0 (1 << 1)                  // Address mark not found
    #define ATA_ERR_1 (1 << 2)                  // Track zero not found
    #define ATA_ERR_2 (1 << 3)                  // Aborted command
    #define ATA_ERR_3 (1 << 4)                  // Media change request
    #define ATA_ERR_4 (1 << 5)                  // ID not found
    #define ATA_ERR_5 (1 << 6)                  // Media changed
    #define ATA_ERR_6 (1 << 7)                  // Uncorrectable data error
    #define ATA_ERR_7 (1 << 8)                  // Bad block detected

    #define ATA_FLUSH 0xE7
    // The system currently only support LBA28 operations, meaning that ports
    // for LBA48 operations are not listed here yet.
    #define ATA_PIO_READ 0x20
    #define ATA_PIO_WRITE 0x30
    #define ATA_DMA_READ 0xC8
    #define ATA_DMA_WRITE 0xCA
    #define ATA_DMA_BUS_MASTER_COMMAND 0xC000
    #define ATA_DMA_BUS_MASTER_STATUS 0xC002
    #define ATA_DMA_BUS_MASTER_PRDT 0xC004
    #define ATA_PRD_TABLE_LENGTH 1

    #include "ctypes.h"

/// fields starting with `d_` are deprecated.
typedef struct s_disk_info {
    uint8_t is_master;
    uint8_t is_found;
    uint8_t is_ata;
    uint8_t support_lba28;
    uint32_t lba28_addr;                            // LBA28 addr count
    uint8_t support_lba48;
    uint64_t lba48_addr;                            // LBA48 addr count
    uint8_t support_udma1;                          // UDMA Mode 1 ...
    uint8_t support_udma2;
    uint8_t support_udma3;
    uint8_t support_udma4;
    uint8_t support_udma5;
    uint8_t support_udma6;
    uint8_t support_udma7;
    uint8_t support_udma8;
    uint8_t active_udma_mode;
    uint8_t udma_up_2_ok;                           // UDMA >2 can be used

    // Values below may get deleted soon.
    unsigned short config_bit;                      // bit      0
    unsigned short d_cylinders[2];                  // bits     1-2
    unsigned short d_heads;                         // bit      3
    unsigned short d_sectors_per_track;             // bit      6
    unsigned short serial_number[10];               // bits     10-19
    unsigned short model_number[19];                // bits     27-46
} t_disk_info;

/// Physical Region Descriptor Table declaration for DMA reading
typedef struct s_prdt {
    uint32_t base;
    uint16_t size;
    uint16_t flags;
} __attribute__((packed)) prdt_t;

void init_dma_prdt(void);
void ata_bsy_wait(uint16_t port);
void ata_drq_wait(uint16_t port);
void ata_drq_err_wait(uint16_t port);
void ata_bmr_wait(uint16_t port);
void pio_lba_write_sector(uint32_t lba_addr, uint16_t *buffer, int len);
void dma_lba_write_sector(uint32_t lba_addr, uint32_t *buffer, uint32_t len);
/// Used to copy some short bytes read from the disk to a target with a
/// offset.
t_disk_info *get_disk_info(void);
uint16_t *pio_lba_read_sector(uint32_t lba_addr);
uint32_t *dma_lba_read_sector(uint32_t lba_addr);

#endif
