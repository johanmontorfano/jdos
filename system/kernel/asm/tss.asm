global flush_tss

flush_tss:
    mov ax, (5 * 8) | 0     ; 5th 8-byte selector
                            ; symb OR-ed with 0 to set RPL
                            ; (Request Privilege Level)
    ltr ax
    ret
