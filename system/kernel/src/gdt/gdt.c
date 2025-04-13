#include "kernel/gdt.h"
#include "ctypes.h"
#include "libc.h"

/// 2 rings defined and one Task State Segment (TSS):
/// |           gdt[x]        |                 Usage               |
/// | ----------------------- | ----------------------------------- |
/// | 0                       | NULL seg                            |
/// | 1                       | Ring 0 data                         |
/// | 2                       | Ring 0 code                         |
/// | 3                       | Ring 3 code                         |
/// | 4                       | Ring 3 data                         |
/// | 5                       | TSS                                 |
static gdt_entry_t gdt[6];
static gdt_descriptor_t gdt_desc;
static tss_entry_t tss;

/// Prepare any gdt entry in `gdt`.
static void set_gdt(gdt_entry_t *entry,
        uint32_t base, uint32_t limit,
        uint8_t access, uint8_t flags)
{
    entry->limit_low = (limit & 0xFFFF);
    entry->base_low = (base & 0xFFFFFF);
    entry->limit_high = (limit >> 16) & 0xF;
    entry->base_high = (base >> 24) & 0xFF;
    entry->accessed = (access > 0) & 1;
    entry->rw = (access >> 1) & 1;
    entry->conforming_expand_down = (access >> 2) & 1;
    entry->code = (access >> 3) & 1;
    entry->code_data_seg = (access >> 4) & 1;
    entry->dpl = (access >> 5) & 0x3;
    entry->present = (access >> 7) & 1;
    entry->available = (flags >> 0) & 1;
    entry->long_mode = (flags >> 1) & 1;
    entry->big = (flags >> 2) & 1;
    entry->gran = (flags >> 3) & 1;
}

/// Write the GDT TSS descriptor and the TSS entry.
static void write_tss(gdt_entry_t *entry) {
    uint32_t base = (uint32_t)&tss;
    uint32_t limit = sizeof(tss_entry_t) - 1;

    mem_set(&tss, 0, sizeof(tss_entry_t));
    tss.ss0 = KERNEL_DATA_SEG;
    tss.esp0 = 0x9FFFF;
    tss.iomap_base = sizeof(tss_entry_t);
    entry->limit_low = limit & 0xFFFF;
    entry->base_low = base & 0xFFFFFF;
    entry->base_high = (base >> 24) & 0xFF;
    entry->accessed = 1;
    entry->rw = 0;
    entry->conforming_expand_down = 0;
    entry->code = 1;
    entry->code_data_seg = 0;
    entry->dpl = 0;
    entry->present = 1;
    entry->limit_high = (limit >> 16) & 0xF;
    entry->available = 0;
    entry->long_mode = 0;
    entry->big = 0;
    entry->gran = 0;
}

/// Will initialize all GDT tables using `set_gdt`
void init_gdt(void)
{
    uint32_t tss_base = (uint32_t)&tss;
    uint32_t tss_limit = sizeof(tss_entry_t);

    set_gdt(&gdt[0], 0, 0, 0, 0);
    set_gdt(&gdt[1], 0, 0xFFFFF, 0x9A, 0xC);
    set_gdt(&gdt[2], 0, 0xFFFFF, 0x92, 0xC);
    set_gdt(&gdt[3], 0, 0xFFFFF, 0xFA, 0xCF);
    set_gdt(&gdt[4], 0, 0xFFFFF, 0xF2, 0xCF);
    write_tss(&gdt[5]);
    gdt_desc.size = sizeof(gdt) - 1;
    gdt_desc.offset = (uint32_t)&gdt;
    asm_load_gdt(&gdt_desc);
    asm volatile (
        "movw %0, %%ax\n"
        "ltr %%ax\n"
        :
        : "i"(TSS_SEG)
        : "ax"
    );
}

/// INFO: Stack is expected to be an address.
void set_kernel_stack(uint32_t stack)
{
    tss.esp0 = stack;
}
