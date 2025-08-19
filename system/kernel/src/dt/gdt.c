#include "kernel/gdt.h"

gdt_t g_gdt[NO_GDT_DESCRIPTORS];
gdt_ptr_t g_gdt_ptr;

void gdt_set_entry(int index, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran) {
    gdt_t *gdt = &g_gdt[index];

    gdt->segment_limit = limit & 0xFFFF;
    gdt->base_low = base & 0xFFFF;
    gdt->base_middle = (base >> 16) & 0xFF;
    gdt->access = access;

    gdt->granularity = (limit >> 16) & 0x0F;
    gdt->granularity = gdt->granularity | (gran & 0xF0);

    gdt->base_high = (base >> 24 & 0xFF);
}

void init_gdt() {
    g_gdt_ptr.limit = sizeof(g_gdt) - 1;
    g_gdt_ptr.base_address = (uint32_t)g_gdt;

    // NULL segment
    gdt_set_entry(0, 0, 0, 0, 0);
    // code segment
    gdt_set_entry(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
    // data segment
    gdt_set_entry(2, 0, 0xFFFFFFFF, 0x92, 0xCF);
    // user code segment
    gdt_set_entry(3, 0, 0xFFFFFFFF, 0xFA, 0xCF);
    // user data segment
    gdt_set_entry(4, 0, 0xFFFFFFFF, 0xF2, 0xCF);

    load_gdt((uint32_t)&g_gdt_ptr);
}
