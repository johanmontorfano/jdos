#ifndef MOD_STDTYPES
    #define MOD_STDTYPES

typedef unsigned char       uint8_t;
typedef unsigned short      uint16_t;
typedef unsigned int        uint32_t;
typedef unsigned long long  uint64_t;

typedef signed char         int8_t;
typedef signed short        int16_t;
typedef signed int          int32_t;
typedef signed long long    int64_t;

/// Can change if the system goes 64-bits. But for now it will remain 32bits.
/// INFO: Switching to 64 bits implies changing the size of size_t.
typedef uint32_t            size_t;

#endif
