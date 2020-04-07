#include "syscall.h"

#define syscall0(NUMBER)     \
    ({                       \
        int retval;          \
        asm volatile(        \
            "mov %1, %%rax;" \
            "syscall"        \
            : "=a"(retval)   \
            : "i"(NUMBER)    \
            : "memory");     \
        retval;              \
    })

#define syscall1(NUMBER, ARG0) \
    ({                         \
        long retval;           \
        asm volatile(          \
            "movq %1, %%rax;"  \
            "movq %2, %%rdi;"  \
            "syscall"          \
            : "=a"(retval)     \
            : "i"(NUMBER),     \
              "g"(ARG0)        \
            : "memory");       \
        retval;                \
    })

#define syscall2(NUMBER, ARG0, ARG1) \
    ({                               \
        int retval;                  \
        asm volatile(                \
            "mov %1, %%rax;"         \
            "mov %2, %%rdi;"         \
            "mov %3, %%rsi;"         \
            "syscall"                \
            : "=a"(retval)           \
            : "i"(NUMBER),           \
              "g"(ARG0),             \
              "g"(ARG1)              \
            : "memory");             \
        retval;                      \
    })

#define syscall3(NUMBER, ARG0, ARG1, ARG2) \
    ({                                     \
        int retval;                        \
        asm volatile(                      \
            "movq %1, %%rax;"              \
            "movq %2, %%rdi;"              \
            "movq %3, %%rsi;"              \
            "movl %4, %%edx;"              \
            "syscall"                      \
            : "=a"(retval)                 \
            : "i"(NUMBER),                 \
              "g"(ARG0),                   \
              "g"(ARG1),                   \
              "g"(ARG2)                    \
            : "memory");                   \
        retval;                            \
    })

#define syscall6(NUMBER, ARG0, ARG1, ARG2, ARG3, ARG4, ARG5) \
    ({                                                       \
        int retval;                                          \
        asm volatile(                                        \
            "movq %1, %%rax;"                                \
            "movq %2, %%rdi;"                                \
            "movq %3, %%rsi;"                                \
            "movl %4, %%edx;"                                \
            "movq %5, %%r10;"                                \
            "movq %6, %%r8;"                                 \
            "movq %7, %%r9;"                                 \
            "syscall"                                        \
            : "=a"(retval)                                   \
            : "i"(NUMBER),                                   \
              "g"(ARG0),                                     \
              "g"(ARG1),                                     \
              "g"(ARG2),                                     \
              "g"(ARG3),                                     \
              "g"(ARG4),                                     \
              "g"(ARG5)                                      \
            : "memory");                                     \
        retval;                                              \
    })

int sys_read(unsigned int fd, char *buf, unsigned count)
{
    return syscall3(SYSREAD, fd, buf, count);
}

int sys_write(unsigned int fd, const char *buf, unsigned count)
{
    return syscall3(SYSWRITE, fd, buf, count);
}

char *sys_mmap(unsigned long addr, unsigned long len, unsigned long prot, unsigned long flags, unsigned long fd, unsigned long off)
{
    return (char *) syscall6(SYSMMAP, addr, len, prot, flags, fd, off);
}

int sys_munmap(unsigned long addr, unsigned long len)
{
    return syscall2(SYSMUNMAP, addr, len);
}

unsigned long sys_brk(unsigned long brk)
{
    return (unsigned long) syscall1(SYSBRK, brk);
}

int sys_access(const char *filename, int mode)
{
    return syscall2(SYSACCESS, filename, mode);
}

int sys_fork()
{
    return syscall0(SYSFORK);
}

int sys_execve(const char *filename, const char *const argv[], const char *const envp[])
{
    return syscall3(SYSEXECVE, filename, argv, envp);
}

void sys_exit(int status)
{
    syscall1(SYSEXIT, status);
}
