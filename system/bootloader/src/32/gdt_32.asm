; The GDT starts with a 8-bit null (2x dd <- 4-bit)
gdt_start:
    dd 0x0
    dd 0x0

; GDT for the code segment
gdt_code:
    dw 0xffff                   ; Segment length
    dw 0x0                      ; Segment base, 0-15
    db 0x0                      ; Segment base, 16-23
    db 10011010b                ; Present, Ring 0, Code, Readable
    db 11001111b                ; Flags (4-bit) + segment length
    db 0x0                      ; Segment base, 24-31

; GDT for data segment
gdt_data:
    dw 0xffff
    dw 0x0
    db 0x0
    db 10010010b                ; Present, Ring 0, Data, Writable
    db 11001111b
    db 0x0

gdt_end:

gdt_descriptor:
    dw gdt_end - gdt_start - 1
    dd gdt_start

; GDT constants for later use
CODE_SEG        equ gdt_code - gdt_start
DATA_SEG        equ gdt_data - gdt_start
