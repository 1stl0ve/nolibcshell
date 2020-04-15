#ifndef __MYLIB_H
#define __MYLIB_H

#define NULL 0

typedef unsigned long long size_t;
#define R_OK 4
#define W_OK 2
#define X_OK 1
#define F_OK 0

typedef long long ssize_t;
typedef unsigned long long size_t;

int access(const char *pathname, int mode);
ssize_t read(int fd, void *buf, size_t count);

int sys_write(unsigned long fd, const char *buf, unsigned long count);
int sys_fork(void);
int sys_execve(const char *filename, const char *const argv[], const char *const envp[]);

#endif
