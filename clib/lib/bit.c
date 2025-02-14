#include "clib.h"
#include "ctypes.h"

/// Return the state of a bit in a 16-bits unsigned number.
/// Zero based: meaning the bits of the number are considered as being ordered:
/// 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
int uint16bitst(uint16_t nb, int bit)
{
    if (nb & (1 << bit))
        return 1;
    return 0;
}
