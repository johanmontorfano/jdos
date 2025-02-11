print:
    pusha                       ; Push all registers here
    jmp print_loop

print_loop:
    mov al, [bx]                ; 'bx' = string base address deref'd
    cmp al, 0                   ; if pointing to NULL, we stop
    je drop_finish

    ; Otherwise, we print the current character
    mov ah, 0x0e
    int 0x10

    ; Increment the pointer to print the next character
    add bx, 1
    jmp print_loop

print_nl:
    pusha

    mov ah, 0x0e
    mov al, 0x0a
    int 0x10
    mov al, 0x0d
    int 0x10

    je drop_finish

drop_finish:
    popa                      ; Pop all registers
    ret                         ; Return the caller
