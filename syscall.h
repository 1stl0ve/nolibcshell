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

int sys_read(unsigned int fd, char *buf, unsigned count);
int sys_write(unsigned int fd, const char *buf, unsigned count);
char *sys_mmap(unsigned long addr, unsigned long len, unsigned long prot, unsigned long flags, unsigned long fd, unsigned long off);
int sys_munmap(unsigned long addr, unsigned long len);
unsigned long sys_brk(unsigned long brk);
int sys_access(const char *filename, int mode);
int sys_fork(void);
int sys_execve(const char *filename, const char *const argv[], const char *const envp[]);
void sys_exit(int status);

#endif
