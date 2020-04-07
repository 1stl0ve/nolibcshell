#include "strings.h"
#include "syscall.h"

#define TRUE 1
#define PROMPT "$ "
#define MAX_BUFF_LEN 2048
#define STDIN 0
#define STDOUT 1
#define STDERR 2
#define NULL 0

int main(int argc, char *Argv[], char *envp[]);

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

int parse_args(char *argv[], char *args)
{
    int i = 0;

    if (args[string_length(args) - 1] != '\n')
    {
        return -1;
    }

    args[string_length(args) - 1] = '\0';

    argv[0] = args;

    for (i = 0; i + 1 < 1024 && argv[i]; i++)
    {
        argv[i + 1] = string_tok(argv[i], ' ');
    }

    return i;
}

void print_prompt(void)
{
    sys_write(STDERR, "$ ", 2);
}

char *getfilename(char *filename, char *envp[])
{
    int i = 0;

    if (filename[0] == '/')
    {
        return NULL;
    }

    for (i = 0; envp[i]; i++)
    {
        if (0 == string_cmp("PATH=", envp[i], 5))
        {
            break;
        }
    }

    char paths_str[MAX_BUFF_LEN] = {0};
    int j = 0;
    for (j = 0; j < string_length(envp[i]); j++)
    {
        paths_str[j] = envp[i][j];
    }

    char *paths[MAX_BUFF_LEN];
    paths[0] = paths_str + 5;
    for (j = 0; j + 1 < MAX_BUFF_LEN && paths[j]; j++)
    {
        paths[j + 1] = string_tok(paths[j], ':');
    }

    for (i = 0; i < j; i++)
    {
        char tmppath[MAX_BUFF_LEN] = {0};
        int k = 0;
        for (k = 0; k < string_length(paths[i]); k++)
        {
            tmppath[k] = paths[i][k];
        }
        tmppath[k] = '/';
        int l = 0;
        for (l = 0; l < string_length(filename); l++)
        {
            tmppath[k + 1 + l] = filename[l];
        }
        int n = sys_access(tmppath, 1);
        if (0 == n)
        {
            unsigned long ret = sys_brk(0);
            ret = sys_brk(ret + string_length(tmppath) + 1);
            int x = 0;
            for (x = 0; x < string_length(tmppath); x++)
            {
                ((char *)ret)[x] = tmppath[x];
            }
            return ret;
        }
    }

    return NULL;
}

int main(int argc, char *argv[], char *envp[])
{
    char buff[MAX_BUFF_LEN] = {0};
    int n = 0;
    char *argv2[1024] = {0};

    while (TRUE)
    {
        sys_write(STDERR, PROMPT, string_length(PROMPT));
        n = read_line(buff, MAX_BUFF_LEN);
        sys_write(STDIN, "[DEBUG] executing: ", string_length("[DEBUG] executing: "));
        sys_write(STDIN, buff, n);

        n = parse_args(argv2, buff);

        if (0 == string_cmp(argv2[0], "exit", 4))
        {
            break;
        }

        int child = sys_fork();

        if (-1 == child)
        {
            sys_exit(1);
        }
        else if (0 == child)
        {
            char *filename = getfilename(argv2[0], envp);
            if (filename)
            {
                argv2[0] = filename;
            }
            if (-1 == sys_execve(argv2[0], argv2, NULL))
            {
                sys_write(STDERR, "execve failed\n", string_length("execve failed\n"));
            }
            if (filename)
            {
                //sys_munmap(filename, 2048);
            }
            sys_exit(0);
        }

        zero_string(buff, MAX_BUFF_LEN);
    }
    return 0;
}
