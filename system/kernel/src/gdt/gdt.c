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
gdt_entry_t *ring3_code = &gdt[3];
gdt_entry_t *ring3_data = &gdt[4];
tss_entry_t tss;


/// Required to enter the ring 3. Should only be ran one time.
/// WARN: The one time running may be wrong, but it seems logical to do it
/// this way. But there is nothing logical about CPUs.
void prepare_ring3(void)
{
    ring3_code->limit_low = 0xFFFF;
    ring3_code->base_low = 0;
    ring3_code->accessed = 0;
    ring3_code->rw = 1;
    ring3_code->conforming_expand_down = 0;
    ring3_code->code = 1;
    ring3_code->code_data_seg = 1;
    ring3_code->dpl = 3;
    ring3_code->present = 1;
    ring3_code->limit_high = 0xF;
    ring3_code->available = 1;
    ring3_code->long_mode = 0;
    ring3_code->big = 1;
    ring3_code->gran = 1;
    ring3_code->base_high = 0;
    *ring3_data = *ring3_code;      // Copies the structure content.
    ring3_data->code = 0;           // Specifies this is a writable seg.
}

void write_tss(gdt_entry_t *from)
{
    uint32_t base = (uint32_t)&tss;
    /// WARN: sizeof usage may create issues.
    uint32_t limit = sizeof(tss_entry_t);

    from->limit_low = base;
    from->base_low = base;
    from->accessed = 1;
    from->rw = 0;
    from->conforming_expand_down = 0;
    from->code = 1;
    from->code_data_seg = 0;
    from->dpl = 0;
    from->present = 1;
    from->limit_high = (limit & (0xF << 16)) >> 16;
    from->available = 0;
    from->long_mode = 0;
    from->big = 0;
    from->gran = 0;
    from->base_high = (base & (0xFF << 24)) >> 24;
    /// Used to ensure TSS is 0'ed.
    mem_set(&tss, 0, sizeof(tss_entry_t));
    /// TODO: REPLACE THOSE PLACEHOLDERS TO MAKE TSS WORK.
    tss.ss0 = /* KERNEL DATA SEGMENT */ 0;
    tss.esp0 = /* KERNEL STACK ADDRESS */ 0;
}

/// INFO: Stack is expected to be an address.
void set_kernel_stack(uint32_t stack)
{
    tss.esp0 = stack;
}
