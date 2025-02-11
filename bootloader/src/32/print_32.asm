[bits 32]                       ; 32-bits mode

VIDEO_MEMORY equ 0xb8000
WHITE_OB_BLACK equ 0x0f

print_string_pm:
    pusha
    mov edx, VIDEO_MEMORY

print_string_pm_loop:
    mov al, [ebx]               ; [ebx] char addr
    mov ah, WHITE_OB_BLACK

    cmp al, 0                   ; End of string condition
    je print_string_pm_done

    mov [edx], ax               ; Store char + attr in VGA memory
    add ebx, 1                  ; Next char
    add edx, 2                  ; Next VGA memory addr

    jmp print_string_pm_loop

print_string_pm_done:
    popa
    ret
