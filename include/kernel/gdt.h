#ifndef KERNEL_GDT
    #define KERNEL_GDT

    #define KERNEL_CODE_SEG (1 << 3)
    #define KERNEL_DATA_SEG (2 << 3)
    #define USER_CODE_SEG   ((3 << 3) | 0x3)
    #define USER_DATA_SEG   ((4 << 3) | 0x3)
    #define TSS_SEG         (5 << 3)

    #include "ctypes.h"


typedef struct s_gdt_descriptor {
    uint16_t size;
    uint32_t offset;
} __attribute__((packed)) gdt_descriptor_t;

typedef struct s_gdt_entry {
    uint16_t limit_low                  : 16;
    uint32_t base_low                   : 24;
    uint8_t accessed                    : 1;
    uint8_t rw                          : 1; // 1 readable (code)
                                             // 0 writable (data)
    uint8_t conforming_expand_down      : 1; // conf for code; exp for data
    uint8_t code                        : 1; // 1 code; 0 data
    uint8_t code_data_seg               : 1; // except if TSS or LDT
    uint8_t dpl                         : 2; // privilege level / ring
    uint8_t present                     : 1;
    uint8_t limit_high                  : 4;
    uint8_t available                   : 1; // software flag/no hw usage
    uint8_t long_mode                   : 1;
    uint8_t big                         : 1;
    uint8_t gran                        : 1; // 1: 4k addring, 0: byte addring
    uint8_t base_high                   : 8;
} __attribute__((packed)) gdt_entry_t;

typedef struct s_tss_entry {
    uint32_t prev_tss;
    uint32_t esp0;
    uint32_t ss0;
    uint32_t esp1;
    uint32_t ss1;
    uint32_t esp2;
    uint32_t ss2;
    uint32_t cr3;
    uint32_t eip;
    uint32_t eflags;
    uint32_t eax;
    uint32_t ecx;
    uint32_t edx;
    uint32_t ebx;
    uint32_t esp;
    uint32_t ebp;
    uint32_t esi;
    uint32_t edi;
    uint32_t es;
    uint32_t cs;
    uint32_t ss;
    uint32_t ds;
    uint32_t fs;
    uint32_t gs;
    uint32_t ldt;
    uint32_t trap;
    uint32_t iomap_base;
} __attribute__((packed)) tss_entry_t;

void init_gdt(void);
void set_kernel_stack(uint32_t stack);
extern void asm_load_gdt(gdt_descriptor_t *);
extern void enter_user_mode(void);

#endif
