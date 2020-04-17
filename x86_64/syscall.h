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
#define SYSWAIT4 61

#define syscall0(NUMBER)     \
    ({                       \
        int retval;          \
        asm volatile(        \
            "movq %1, %%rax;" \
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
            "movq %1, %%rax;"         \
            "movq %2, %%rdi;"         \
            "movq %3, %%rsi;"         \
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

#define syscall4(NUMBER, ARG0, ARG1, ARG2, ARG3) \
    ({                                           \
        long retval;                             \
        asm volatile(                            \
            "movq %1, %%rax;"                    \
            "movq %2, %%rdi;"                    \
            "movq %3, %%rsi;"                    \
            "movq %4, %%rdx;"                    \
            "movq %5, %%r10;"                    \
            "syscall"                            \
            : "=a"(retval)                       \
            : "i"(NUMBER),                       \
              "g"(ARG0),                         \
              "g"(ARG1),                         \
              "g"(ARG2),                         \
              "g"(ARG3)                          \
            : "memory");                         \
        retval;                                  \
    })

#endif
