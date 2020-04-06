#include "syscall.h"

#define true 1

int main(void);

void
_start(void)
{
    int retval = main();
    sys_exit(retval);
}

void
print_prompt(void)
{
    sys_write(2, "$ ", 2);
}

int
main(void)
{
    while (true)
    {
        print_prompt();
        char buff[2048] = {0};
        int n = sys_read(0, buff, 2048);
        sys_write(1, "Read: ", 6);
        sys_write(1, buff, n);
    }
    return 0;
}