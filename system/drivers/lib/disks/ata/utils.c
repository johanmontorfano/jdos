#include "drivlib/ata.h"
#include "drivlib.h"
#include "ctypes.h"
#include "clib.h"

void short_cpy(uint16_t *data, uint16_t *target, int p, int s)
{
    int i = 0;

    while (i < s) {
        target[i] = data[p + i];
        i++;
    }
}

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
