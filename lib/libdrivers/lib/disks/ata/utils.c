#include "drivlib/ata.h"
#include "drivlib.h"
#include "ctypes.h"

/// Waits for the BSY bit to be cleared.
void ata_bsy_wait(uint16_t port)
{
    while (readb_port(port) & 0x80);
}

/// Waits for the DRQ bit to be cleared.
void ata_drq_wait(uint16_t port)
{
    while (!(readb_port(port) & 0x08));
}

/// Waits for the DRQ bit or ERR bit to be set.
void ata_drq_err_wait(uint16_t port)
{
    while (!(readb_port(port) & 0x08) && !(readb_port(port) & 0x01));
}

/// Waits for the BMR active byte to clear
void ata_bmr_wait(uint16_t port)
{
    while (readb_port(port) & 0x04);
}
