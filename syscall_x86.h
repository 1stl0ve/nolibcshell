#ifndef __SYSCALL_H
#define __SYSCALL_H

#define SYSEXIT 1
#define SYSFORK 2
#define SYSREAD 3
#define SYSWRITE 4
#define SYSEXECVE 11
#define SYSACCESS 33
#define SYSBRK 45
#define SYSWAIT4 114

#define syscall0(NUMBER)           \
    ({                             \
        int retval;                \
        asm volatile(              \
            "push %%eax;"          \
            "movl %1, %%eax;"      \
            "int $0x80"            \
            : "=a"(retval)         \
            : "i"(NUMBER)          \
            : "memory");           \
        asm volatile("pop %eax;"); \
        retval;                    \
    })

#define syscall1(NUMBER, ARG0)               \
    ({                                       \
        int retval;                          \
        asm volatile(                        \
            "push %%eax; push %%ebx;"        \
            "movl %1, %%eax;"                \
            "movl %2, %%ebx;"                \
            "int $0x80"                      \
            : "=a"(retval)                   \
            : "i"(NUMBER),                   \
              "g"(ARG0)                      \
            : "memory");                     \
        asm volatile("pop %ebx; pop %eax;"); \
        retval;                              \
    })

#define syscall2(NUMBER, ARG0, ARG1)                   \
    ({                                                 \
        int retval;                                    \
        asm volatile(                                  \
            "push %%eax; push %%ebx; push %%ecx;"      \
            "movl %1, %%eax;"                          \
            "movl %2, %%ebx;"                          \
            "movl %3, %%ecx;"                          \
            "int $0x80"                                \
            : "=a"(retval)                             \
            : "i"(NUMBER),                             \
              "g"(ARG0),                               \
              "g"(ARG1)                                \
            : "memory");                               \
        asm volatile("pop %ecx; pop %ebx; pop %eax;"); \
        retval;                                        \
    })

#define syscall3(NUMBER, ARG0, ARG1, ARG2)                       \
    ({                                                           \
        int retval;                                              \
        asm volatile(                                            \
            "push %%eax; push %%ebx; push %%ecx; push %%edx;"    \
            "movl %1, %%eax;"                                    \
            "movl %2, %%ebx;"                                    \
            "movl %3, %%ecx;"                                    \
            "movl %4, %%edx;"                                    \
            "int $0x80"                                          \
            : "=a"(retval)                                       \
            : "i"(NUMBER),                                       \
              "g"(ARG0),                                         \
              "g"(ARG1),                                         \
              "g"(ARG2)                                          \
            : "memory");                                         \
        asm volatile("pop %edx; pop %ecx; pop %ebx; pop %eax;"); \
        retval;                                                  \
    })

#define syscall4(NUMBER, ARG0, ARG1, ARG2, ARG3)                           \
    ({                                                                     \
        int retval;                                                        \
        asm volatile(                                                      \
            "push %%eax; push %%ebx; push %%ecx; push %%edx; push %%esi;"  \
            "movl %1, %%eax;"                                              \
            "movl %2, %%ebx;"                                              \
            "movl %3, %%ecx;"                                              \
            "movl %4, %%edx;"                                              \
            "movl %5, %%esi;"                                              \
            "int $0x80"                                                    \
            : "=a"(retval)                                                 \
            : "i"(NUMBER),                                                 \
              "g"(ARG0),                                                   \
              "g"(ARG1),                                                   \
              "g"(ARG2),                                                   \
              "g"(ARG3)                                                    \
            : "memory");                                                   \
        asm volatile("pop %esi; pop %edx; pop %ecx; pop %ebx; pop %eax;"); \
        retval;                                                            \
    })

#endif
