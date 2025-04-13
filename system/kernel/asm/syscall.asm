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
; WARN: This expects to run in ring 3
; INFO: The sysenter instruction is not present here since this piece of code
; will be ran
;
; Register  | Content
; --------------------------------------------
; eax       | Syscall number
section .text
syscall_entry:
    ; Save caller-saved registers
    push eax
    push ecx
    push edx

    ; Save user return address context (passed by user)
    ; ECX = return EIP
    ; EDX = return ESP
    push ecx    ; Save EIP
    push edx    ; Save ESP

    ; Get syscall number back
    pop edx     ; Restore ESP into EDX
    pop ecx     ; Restore EIP into ECX
    pop eax     ; Restore syscall number into EAX

    ; Frame for C call
    push ebp
    mov ebp, esp

    call system_call

    pop ebp

    ; Now restore EDX = user ESP, ECX = user EIP (in this order!)
    ; They're still in registers from above, no need to reload

    sysexit     ; ↘ CPU switches ring + sets EIP = ECX, ESP = EDX
