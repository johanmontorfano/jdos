ENTRY(_start)

SECTIONS
{
    /* Kernel offset: 4kb */
    . = 0x1000;

    .text : {
        *(.text._start)
        *(.text)
    }

    .rodata : {
        *(.rodata)
    }

    .data : {
        *(.data)
    }

    .bss : {
        *(.bss)
    }
}
