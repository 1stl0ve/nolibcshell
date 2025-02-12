#ifndef __MYLIB_H
#define __MYLIB_H

#define NULL 0

#ifdef ARCH32
typedef unsigned int size_t;
typedef int ssize_t;
#else
typedef unsigned long long size_t;
typedef long long ssize_t;
#endif

/**
 * constants for access modes.
 */
#define R_OK 4
#define W_OK 2
#define X_OK 1
#define F_OK 0

/**
 * constants for waitpid options.
 */
#define __WALL 0x40000000

#define assert(expression) \
    ({                     \
        if (!(expression)) \
        {                  \
            exit(1);       \
        }                  \
    })

/**
 * @brief wrapper function for access syscall.
 */
int access(const char *pathname, int mode);

/**
 * @brief wrapper function for read syscall.
 */
ssize_t read(int fd, void *buf, size_t count);

/**
 * @brief wrapper function for fork syscall.
 */
int fork(void);

/**
 * @brief wrapper function for wait4 syscall.
 */
int waitpid(int pid, int *wstatus, int options);

/**
 * @brief wrapper function for execve syscall.
 */
int execve(const char *filename, const char *const argv[], const char *const envp[]);

/**
 * @brief wrapper function for exit syscall.
 */
void exit(int status);

#endif
