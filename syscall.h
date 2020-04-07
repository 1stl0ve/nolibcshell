#ifndef __SYSCALL_H
#define __SYSCALL_H

#define SYSREAD 0
#define SYSWRITE 1
#define SYSFORK 57
#define SYSEXECVE 59
#define SYSEXIT 60

int sys_read(unsigned int fd, char *buf, unsigned count);
int sys_write(unsigned int fd, const char *buf, unsigned count);
int sys_fork(void);
int sys_execve(const char *filename, const char *const argv[], const char *const envp[]);
void sys_exit(int status);

#endif
