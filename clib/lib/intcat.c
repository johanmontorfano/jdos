#include "ctypes.h"
#include "clib.h"
#include "drivlib.h"

/// Combine two uint16_t values into a uint32_t
uint32_t ui16c32(uint16_t a, uint16_t b)
{
    write_uint(a);
    print(" ");
    write_uint(b);
    print("\n");
    return ((uint32_t)a << 16) | b;
}

/// Combine two uint32_t into a uint64_t
uint64_t ui32c64(uint32_t a, uint32_t b)
{
    return ((uint64_t)a << 32) | b;
}

uint64_t ui16c64(uint16_t a, uint16_t b, uint16_t c, uint16_t d)
{
    return ui32c64(ui16c32(a, b), ui16c32(c, d));
}


