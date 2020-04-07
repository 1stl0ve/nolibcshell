.text
.global _start
_start:
    popq %rdi
    mov %rsp, %rsi
    leaq 8(%rsp,%rdi,8), %rdx
    call main
    mov %rax, %rdi
    mov $60, %rax
    syscall