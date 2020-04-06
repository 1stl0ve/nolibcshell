#ifndef __SYSCALL_H
#define __SYSCALL_H

#define SYSREAD 0
#define SYSWRITE 1
#define SYSEXIT 60

int sys_read(unsigned int fd, char *buf, unsigned count);
int sys_write(unsigned int fd, const char *buf, unsigned count);
void sys_exit(int status);

#endif
