#ifndef __UNISTD_H
#define __UNISTD_H

#define R_OK 4
#define W_OK 2
#define X_OK 1
#define F_OK 0

int access(const char *pathname, int mode);

#endif
