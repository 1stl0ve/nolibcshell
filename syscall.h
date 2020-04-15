#ifndef __SYSCALL_H
#define __SYSCALL_H

#define SYSREAD 0
#define SYSWRITE 1
#define SYSMMAP 9
#define SYSMUNMAP 11
#define SYSBRK 12
#define SYSACCESS 21
#define SYSFORK 57
#define SYSEXECVE 59
#define SYSEXIT 60

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
        long retval;                  \
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
        long retval;                       \
        asm volatile(                      \
            "movq %1, %%rax;"              \
            "movq %2, %%rdi;"              \
            "movq %3, %%rsi;"              \
            "movq %4, %%rdx;"              \
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


#if 0
int sys_read(unsigned int fd, char *buf, unsigned count);
//int sys_write(unsigned int fd, const char *buf, unsigned int count);
int sys_write(unsigned long fd, const char *buf, unsigned long count);
char *sys_mmap(unsigned long addr, unsigned long len, unsigned long prot, unsigned long flags, unsigned long fd, unsigned long off);
int sys_munmap(unsigned long addr, unsigned long len);
unsigned long sys_brk(unsigned long brk);
int sys_access(const char *filename, int mode);
int sys_fork(void);
int sys_execve(const char *filename, const char *const argv[], const char *const envp[]);
void sys_exit(int status) __attribute__((noreturn));
#endif

#endif
