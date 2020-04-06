#include "strings.h"
#include "syscall.h"

#define TRUE 1
#define PROMPT "$ "
#define MAX_BUFF_LEN 2048
#define STDIN 0
#define STOUT 1
#define STDERR 2

int main(void);

void _start(void)
{
    int retval = main();
    sys_exit(retval);
}

int read_line(char *buff, unsigned length)
{
    int i = 0;
    char c = '\0';
    do
    {
        sys_read(0, &c, 1);
        buff[i++] = c;
    } while (c != '\n' && i < length);

    return i;
}

void print_prompt(void)
{
    sys_write(STDERR, "$ ", 2);
}

int main(void)
{
    char buff[MAX_BUFF_LEN] = {0};
    int n = 0;
    while (TRUE)
    {
        sys_write(STDERR, PROMPT, string_length(PROMPT));
        n = read_line(buff, MAX_BUFF_LEN);
        sys_write(STDIN, "Read: ", 6);
        sys_write(STDIN, buff, n);

        if (0 == string_cmp(buff, "exit", 4))
        {
            break;
        }

        zero_string(buff, MAX_BUFF_LEN);
    }
    return 0;
}
