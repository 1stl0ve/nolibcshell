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
        int retval;            \
        asm volatile(          \
            "mov %1, %%rax;"   \
            "mov %2, %%rdi;"   \
            "syscall"          \
            : "=a"(retval)     \
            : "i"(NUMBER),     \
              "g"(ARG0)        \
            : "memory");       \
        retval;                \
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

int sys_write(unsigned int fd, const char *buf, unsigned count)
{
    return syscall3(SYSWRITE, fd, buf, count);
}

int sys_read(unsigned int fd, char *buf, unsigned count)
{
    return syscall3(SYSREAD, fd, buf, count);
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
