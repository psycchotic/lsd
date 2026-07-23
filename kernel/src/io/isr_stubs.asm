; --- idt.asm ---
bits 64

; Macro for exceptions that DO NOT push an error code automatically
%macro EXCEPTION_NO_ERR_CODE 1
global exception_handler_%1
exception_handler_%1:
    push qword 0    ; Dummy error code to keep stack uniform
    push qword %1   ; Push the interrupt number
    jmp common_exception_wrapper
%endmacro

; Macro for exceptions that DO push an error code automatically
%macro EXCEPTION_WITH_ERR_CODE 1
global exception_handler_%1
exception_handler_%1:
                    ; Error code is already pushed by the CPU
    push qword %1   ; Push the interrupt number
    jmp common_exception_wrapper
%endmacro

; Generate handlers 0 to 31
%assign i 0
%rep 32
    ; Check if 'i' is an exception that pushes an error code
    %if i == 8 || (i >= 10 && i <= 14) || i == 17 || i == 21 || i == 29 || i == 30
        EXCEPTION_WITH_ERR_CODE i
    %else
        EXCEPTION_NO_ERR_CODE i
    %endif
%assign i i+1
%endrep

extern c_exception_handler

common_exception_wrapper:
    ; Save all general-purpose registers (System V AMD64 ABI)
    push rbp
    push r15
    push r14
    push r13
    push r12
    push r11
    push r10
    push r9
    push r8
    push rdi
    push rsi
    push rdx
    push rcx
    push rbx
    push rax

    ; Pass the stack pointer as the first argument to the C function (rdi)
    mov rdi, rsp
    
    ; Call the C handler
    call c_exception_handler

    ; Restore all general-purpose registers
    pop rax
    pop rbx
    pop rcx
    pop rdx
    pop rsi
    pop rdi
    pop r8
    pop r9
    pop r10
    pop r11
    pop r12
    pop r13
    pop r14
    pop r15
    pop rbp


    add rsp, 16     
    
    iretq

section .data
global g_exception_handlers_table

g_exception_handlers_table:
%assign i 0
%rep 32
    dq exception_handler_%[i]
%assign i i+1
%endrep


