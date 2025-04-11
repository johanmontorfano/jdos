[extern system_call]
global syscall_entry

; We are implementing system calls using `Fast System Calls`. Even if this
; implies using `sysenter` and `sysexit` - hence working in x86 CPUs, we do
; not expect this project from ever reaching a stage where kernel/user mode
; in all CPUs is required.
; In oppposition to using interrupts for system calls, the `sys` instructions
; are not copying register. Thus, a lot of the code below is linked to
; register managment.
; WARN: This code expects a C function call `system_call` to be defined since
; it will be the function called to manage the syscall.
; INFO: The sysenter instruction is not present here since this piece of code
; will be ran
;
; Register  | Content
; --------------------------------------------
; eax       | Syscall number
section .text
syscall_entry:
    mov ecx, esp     ; Store user ESP in ECX
    push ecx         ; Save user ESP on kernel stack
    push ebp
    mov ebp, esp
    push eax  ; Syscall number

    call system_call

    pop eax
    pop ecx          ; Load saved ESP
    mov esp, ecx     ; Restore user stack
    mov edx, 0x23    ; User Data Segment (Ring 3)
    mov ss, edx      ; Set user stack segment
    mov ecx, 0x1B    ; User Code Segment (Ring 3)
    push ecx         ; Push CS for sysexit
    push eax         ; Push return EIP
    sysexit          ; Fast return to user mode
