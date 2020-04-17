.text
.global _start

_start:
    pop %edi
    mov %esp, %esi
    lea 4(%esp,%edi,4), %edx
    push %edx
    push %esi
    push %edi
    call main
    mov %eax, %ebx
    mov $1, %eax
    int $0x80