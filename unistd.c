#include "syscall.h"

int access(const char *pathname, int mode)
{
    return sys_access(pathname, mode);
}