[org 0x7c00]                    ; Bootloader offset
KERNEL_OFFSET equ 0x1000        ; Offset used by the linker

    mov [BOOT_DRIVE], dl
    mov bp, 0x9000
    mov sp, bp
    mov bx, MSG_REAL_MODE
    call print
    call print_nl

    call load_kernel
    call switch_to_pm
    jmp $                       ; Unreachable

%include "src/disk.asm"
%include "src/print.asm"
%include "src/print_hex.asm"
%include "src/32/gdt_32.asm"
%include "src/32/print_32.asm"
%include "src/32/switch_32.asm"

[bits 16]
load_kernel:
    mov bx, MSG_LOAD_KERN
    call print
    call print_nl

    mov bx, KERNEL_OFFSET
    mov dh, 44                  ; Kernel size
    mov dl, [BOOT_DRIVE]
    call disk_load
    ret

[bits 32]
BEGIN_PM:                       ; switch_to_pm will redirect to here
    mov ebx, MSG_PROT_MODE
    call print_string_pm
    call KERNEL_OFFSET
    jmp $

BOOT_DRIVE db 0
MSG_REAL_MODE db "Started in 16-bit real mode", 0
MSG_PROT_MODE db "Loaded 32-bit protected mode", 0
MSG_LOAD_KERN db "Loading kernel into memory", 0

; Bootsector
times 510 - ($-$$) db 0
dw 0xaa55
