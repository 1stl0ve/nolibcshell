#include "unistd.h"
#include "syscall.h"

int access(const char *pathname, int mode)
{
    return syscall2(SYSACCESS, pathname, mode);
}

ssize_t read(int fd, void *buf, size_t count)
{
    return (ssize_t) syscall3(SYSREAD, fd, buf, count);
}

int sys_write(unsigned long fd, const char *buf, unsigned long count)
{
    return syscall3(SYSWRITE, fd, buf, count);
}

int sys_fork()
{
    return syscall0(SYSFORK);
}

int sys_execve(const char *filename, const char *const argv[], const char *const envp[])
{
    return syscall3(SYSEXECVE, filename, argv, envp);
}