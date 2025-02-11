; Prints context hexadecimally, thus can print addresses
print_hex:
    pusha                       ; Push all registers here
    mov cx, 0                   ; Index variable

; Strategy: get the last char of 'dx', convert it to ASCII
; Numeric: +30
; Alphabetic: +40
hex_loop:
    cmp cx, 4                   ; Loop 4 times
    je end

    ; Convert the last char of 'dx' to ASCII
    mov ax, dx
    and ax, 0x000f              ; Masks the first three
    add al, 0x30
    cmp al, 0x39
    jle hex_get_pos
    add al, 7

hex_get_pos:
    mov bx, HEX_OUT + 5
    sub bx, cx
    mov [bx], al
    ror dx, 4

    add cx, 1
    jmp hex_loop

end:
    mov bx, HEX_OUT
    call print

    popa
    ret

HEX_OUT:
    db '0x0000', 0              ; String memory
