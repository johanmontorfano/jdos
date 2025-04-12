global asm_load_gdt
global enter_user_mode
[extern usermode]

asm_load_gdt:
    mov eax, [esp + 4]
    lgdt [eax]
    ret

enter_user_mode:
    cli                             ; Disable interrupts just before switch

    mov ax, USER_DATA_SEG
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    mov eax, 0xB0000                ; User-mode stack pointer
    push 0x23
    push eax
    pushf
    push 0x1B
    push usermode
    iret

USER_CODE_SEG equ 0x1B
USER_DATA_SEG equ 0x23
