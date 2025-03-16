; Load 'dh' sectors from 'dl' drive into es:bx
; 'dl' <- drive number (0 = floppy, 1 = floppy2, 0x80 = hdd, 0x01 = hdd2)
disk_load:
    pusha
    push dx

    mov ah, 0x02                ; 'read' function
    mov al, dh                  ; 'al' = number of sectors to read
    mov cl, 0x02                ; First available sector (0x01 = boot sector)
    mov ch, 0x00                ; Cylinder
    mov dh, 0x00                ; Head number

    int 0x13                    ; Interrupt
    jc disk_error               ; Error stored in the carry bit

    pop dx
    cmp al, dh
    jne sectors_error
    popa
    ret

disk_error:
    mov bx, DISK_ERROR
    call print
    call print_nl
    mov dh, ah
    call print_hex
    jmp disk_loop

sectors_error:
    mov bx, SECTORS_ERROR
    call print

disk_loop:
    jmp $

DISK_ERROR: db "Disk read error", 0
SECTORS_ERROR: db "Incorrect number of sectors read", 0
