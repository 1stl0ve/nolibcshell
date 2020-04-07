#include <stdlib.h>
#include "unistd.h"
#include "strings.h"
#include "syscall.h"

#define TRUE 1
#define PROMPT "$ "
#define MAX_BUFF_LEN 2048
#define STDIN 0
#define STDOUT 1
#define STDERR 2

int main(int argc, char *argv[], char *envp[]);

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

    if (args[strlen(args) - 1] != '\n')
    {
        return -1;
    }

    args[strlen(args) - 1] = '\0';

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

char *search_path(char *cmd, char *env_path)
{
    char *paths[MAX_BUFF_LEN];
    char *path = NULL;
    int path_len = 0;
    int i = 0;
    int status = 0;

    /*
     * Create an array containing each of the potential path elements by tokenizing
     * env_path on ':'
     */
    paths[0] = env_path;
    for (i = 0; i + 1 < MAX_BUFF_LEN && paths[i]; i++)
    {
        paths[i + 1] = string_tok(paths[i], ':');
    }

    for (i = 0; i + 1 < MAX_BUFF_LEN && paths[i]; i++)
    {
        path_len = strlen(paths[i]) + 1 + strlen(cmd) + 1; /* +2 for '/' and null byte. */
        path = malloc(path_len * sizeof(char));
        if (!path)
        {
            return NULL;
        }
        memset(path, 0, path_len);

        /* 
         * construct the binary path: path + / + cmd 
         */
        memcpy(path, paths[i], strlen(paths[i]));
        memcpy(path + strlen(paths[i]), "/", 1);
        memcpy(path + strlen(paths[i]) + 1, cmd, strlen(cmd));

        /*
         * check to see if that binary exists and is executable.
         */
        status = access(path, X_OK);
        if (0 == status)
        {
            return path;
        }

        /* 
         * no good. 
         */
        free(path);
    }
    return NULL;
}

char *get_command_path(char *cmd, char *envp[])
{
    char path_str[MAX_BUFF_LEN] = {0};
    char *path = NULL;
    int i = 0;

    /*
     * if the command starts with a '/', assume its an absolute path.
     * return NULL to tell the calling function to use what it already has.
     */
    if (cmd[0] == '/')
    {
        return NULL;
    }

    /* 
     * search the environment for PATH.
     */
    for (i = 0; envp[i]; i++)
    {
        if (0 == strncmp("PATH=", envp[i], 5))
        {
            break;
        }
    }

    /*
     * copy the PATH variable (starting after '=') to path_str.
     */
    if (envp)
    {
        path = envp[i] + 5;
        strncpy(path_str, path, strlen(path));
    }

    return search_path(cmd, path_str);

}

int main(int argc, char *argv[], char *envp[])
{
    char buff[MAX_BUFF_LEN] = {0};
    int n = 0;
    char *argv2[1024] = {0};

    while (TRUE)
    {
        sys_write(STDERR, PROMPT, strlen(PROMPT));
        n = read_line(buff, MAX_BUFF_LEN);
        sys_write(STDIN, "[DEBUG] executing: ", strlen("[DEBUG] executing: "));
        sys_write(STDIN, buff, n);

        n = parse_args(argv2, buff);

        if (0 == strncmp(argv2[0], "exit", 4))
        {
            break;
        }

        char *filename = get_command_path(argv2[0], envp);
        if (filename)
        {
            argv2[0] = filename;
        }
        int child = sys_fork();

        if (-1 == child)
        {
            exit(1);
        }
        else if (0 == child)
        {

            if (-1 == sys_execve(argv2[0], (const char *const *)argv2, NULL))
            {
                sys_write(STDERR, "execve failed\n", strlen("execve failed\n"));
            }
            if (filename)
            {
                free(filename);
            }
            exit(0);
        }

        if (filename)
        {
            free(filename);
        }
        memset(buff, 0, MAX_BUFF_LEN);
    }
    return 0;
}
