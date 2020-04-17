/**
 * A series of wrapper functions for syscalls needed by the shell.
 */
#include "mylib.h"
#ifdef ARCH32
#include "syscall_x86.h"
#else
#include "syscall.h"
#endif

/**
 * access:
 * @brief wrapper function for access syscall.
 * 
 * @param pathname - the path to check permissions
 * @param mode - accessibility checks to conduct.
 * @return 0 on success; -1 on error.
 */
int access(const char *pathname, int mode)
{
    return syscall2(SYSACCESS, pathname, mode);
}

/**
 * read:
 * @brief wrapper function for read syscall.
 * 
 * @param fd - file descriptor to read from.
 * @param buf - the buffer to write read bytes to.
 * @param count - the number of bytes to read.
 */
ssize_t read(int fd, void *buf, size_t count)
{
    return (ssize_t) syscall3(SYSREAD, fd, buf, count);
}

/**
 * fork:
 * @brief wrapper function for fork syscall.
 * 
 * @return pid of child process in parent; 0 in child; -1 on error.
 */
int fork()
{
    return syscall0(SYSFORK);
}

/**
 * waitpid:
 * @brief wrapper function for wait4 syscall.
 * 
 * @param pid - pid to wait for
 * @param wstatus - pointer to wait status
 * @param options - wait options
 * 
 * @return pid of child on success; -1 on error.
 */
int waitpid(int pid, int *wstatus, int options)
{
    return syscall4(SYSWAIT4, pid, wstatus, options, NULL);
}

/**
 * execve:
 * @brief wrapper function for execve syscall.
 * 
 * @param filename - the executable to execute.
 * @param argv - an array of arguments.
 * @param envp - an array of environment variables.
 * @return does not return on success; -1 on error.
 */
int execve(const char *filename, const char *const argv[], const char *const envp[])
{
    return syscall3(SYSEXECVE, filename, argv, envp);
}

/**
 * exit:
 * @brief wrapper function for exit syscall.
 * 
 * @param status - value to return on exit.
 * @return does not return.
 */
void exit(int status)
{
    syscall1(SYSEXIT, status);
    /* does not return. */
    __builtin_unreachable();
}
