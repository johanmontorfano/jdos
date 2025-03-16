[org 0x7c00]                        ; Boot sector code offset.
    mov bp, 0x8000                  ; Safe stack address
    mov sp, bp
    mov bx, 0x9000                  ; es:bx = 0x0000:0x9000 = 0x9000
    mov dh, 2                       ; Read 2 sectors
    call disk_load

    mov dx, [0x9000]                ; Retrieve the first loaded word of sec1
    call print_hex
    call print_nl

    mov dx, [0x9000 + 512]          ; Retrieve the first work of sec2
    call print_hex
    jmp $

%include "src/disk.asm"
%include "src/print.asm"
%include "src/print_hex.asm"

; Data
OS_LABEL_NAME: db 'JOS', 0
OS_LABEL_START: db 'Starting...', 0

; Padding and magic number
times 510-($-$$) db 0
dw 0xaa55

times 256 dw 0xdada
times 256 dw 0xface
