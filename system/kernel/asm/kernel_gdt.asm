global load_kernel_gdt
global gdt_descriptor
global enter_user_mode
[extern usermode]

; Enter user-mode from the kernel, allowing system calls, ... to work.
enter_user_mode:
    mov ax, (USER_DATA_SEG | 0x3)        ; Set user mode data segment
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    mov ss, ax               ; Set user stack segment
    mov esp, 0xB0000         ; Set user stack

    push USER_DATA_SEG       ; SS (Stack Segment)
    push esp                 ; ESP (Stack Pointer)
    pushf                    ; Push EFLAGS (Interrupts enabled)
    push USER_CODE_SEG       ; CS (Code Segment)
    push usermode            ; EIP (User Mode Entry Point)
    iret                     ; Interrupt Return -> Jumps to User Mode

user_entry:
    mov ebx, 0
    mov eax, 1
    int 0x80                 ; Example syscall from user mode

    hlt                      ; Halt when finished

section .data
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

; GDT code segment for user-space (Ring 3)
gdt_user_code:
    dw 0xffff
    dw 0x0
    dw 0x0
    db 11111010b                ; Present, Ring 3, Code, Readable
    db 11001111b
    db 0x0

; GDT data segment for user-space (Ring 3)
gdt_user_data:
    dw 0xffff
    dw 0x0
    dw 0x0
    db 11110010b                ; Present, Ring 3, Data, Writable
    db 11001111b
    db 0x0

gdt_end:

gdt_descriptor:
    dw gdt_end - gdt_start - 1
    dd gdt_start

load_kernel_gdt:
    lgdt [gdt_descriptor]
    ret

; GDT constants for later use
CODE_SEG        equ gdt_code - gdt_start
DATA_SEG        equ gdt_data - gdt_start
USER_CODE_SEG   equ gdt_user_code - gdt_start
USER_DATA_SEG   equ gdt_user_data - gdt_start
