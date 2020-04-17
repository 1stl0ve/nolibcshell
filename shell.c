#include "mylib.h"
#include "heap.h"
#include "strings.h"

#define MAX_BUFF_LEN 2048
#define STDIN 0
#define STDOUT 1
#define STDERR 2

int main(int argc, char *argv[], char *envp[]);

/**
 * read_line:
 * @brief reads a line of input from stdin.
 * 
 * This function reads from std in until either a new line character is encountered or
 * a length limit has been reached.
 * 
 * @param buff - the buffer to write the input to.
 * @param length - the maximum number of bytes to read.
 * @return the total number of bytes read.
 */
int read_line(char *buff, unsigned int length)
{
    unsigned int i = 0;
    char c = '\0';

    assert(NULL != buff);

    do
    {
        read(STDIN, &c, 1);
        buff[i++] = c;
    } while (c != '\n' && i < length);

    return i;
}

/**
 * parse_args:
 * @brief parses a string of arguments separated by a space and write them into an array.
 * 
 * @param argv - the array of strings to write each argument to.
 * @param args - a string of all arguments separated by spaces.
 * @return the number of arguments.
 */
int parse_args(char *argv[], char *args)
{
    int i = 0;

    assert(NULL != argv);
    assert(NULL != args);

    /**
     * only accept arguments that are terminated with a new line (i.e. a user pressed
     * the enter key after typing a command).
     */
    if (args[strlen(args) - 1] != '\n')
    {
        return -1;
    }

    /**
     * we do not want the new line character in our output though...
     */
    args[strlen(args) - 1] = '\0';

    /**
     * parse the arguments using the home-brewed strtok.
     * 
     * NOTE: this strtok returns a pointer to after the _next_ instance of a delimeter.
     */
    argv[0] = args;
    for (i = 0; i + 1 < 1024 && argv[i]; i++)
    {
        argv[i + 1] = strtok(argv[i], ' ');
    }

    return i;
}

/**
 * search_path:
 * @brief search the PATH env variable to resolve a command.
 * 
 * This function iterates through each path in the PATH env variable and checks to see if
 * path/cmd is a valid executable.
 * 
 * Base on the example from: https://stackoverflow.com/questions/147057/ 
 * 
 * @param cmd - the command to execute.
 * @param env_path - the PATH env variable
 * @return a pointer to a valid path; NULL on error.
 */
char *search_path(char *cmd, char *env_path)
{
    char *paths[MAX_BUFF_LEN];
    char *path = NULL;
    int path_len = 0;
    int i = 0;
    int status = 0;

    assert(NULL != cmd);
    assert(NULL != env_path);

    /**
     * Create an array containing each of the potential path elements by tokenizing
     * env_path on ':'
     */
    paths[0] = env_path;
    for (i = 0; i + 1 < MAX_BUFF_LEN && paths[i]; i++)
    {
        paths[i + 1] = strtok(paths[i], ':');
    }

    for (i = 0; i + 1 < MAX_BUFF_LEN && paths[i]; i++)
    {
        path_len = strlen(paths[i]) + 1 + strlen(cmd) + 1; /* +2 for '/' and null byte. */
        path = malloc(path_len * sizeof(char));
        if (NULL == path)
        {
            goto done;
        }
        memset(path, 0, path_len);

        /** 
         * construct the binary path: path + / + cmd 
         */
        strncpy(path, paths[i], strlen(paths[i]));
        strncpy(path + strlen(paths[i]), "/", 1);
        strncpy(path + strlen(paths[i]) + 1, cmd, strlen(cmd));

        /**
         * check to see if that binary exists and is executable.
         */
        status = access(path, X_OK);
        if (0 == status)
        {
            goto done;
        }

        /* 
         * no good. 
         */
        free(path);
        path = NULL;
    }

done:
    return path;
}

char *get_command_path(char *cmd, char *envp[])
{
    char path_str[MAX_BUFF_LEN] = {0};
    char *path = NULL;
    int i = 0;

    assert(NULL != cmd);
    assert(NULL != envp);

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

/**
 * main:
 * @brief runs main shell loop.
 * 
 * @param argc - number of arguments
 * @param argv - array of arguments
 * @param envp - array of env variables
 * @return 0 on success; other value on error;
 */
int main(int argc, char *argv[], char *envp[])
{
    char buff[MAX_BUFF_LEN] = {0};
    char *argv2[1024] = {0};
    char *prompt = "$ ";
    char *filename = NULL;
    int status = 0;
    int n = 0;
    int background = 0;
    int child = 0;

    /**
     * ignore unused arguments.
     */
    (void) argc;
    (void) argv;

    /**
     * loop through commands.
     */
    for (;;)
    {
        /**
         * get the user's input and parse the arguments.
         */
        printstr(STDERR, prompt);
        read_line(buff, MAX_BUFF_LEN);
        n = parse_args(argv2, buff);

        /**
         * if there isn't any command, loop back around to get another one.
         */
        if (0 == strncmp(argv2[0], "", 1))
        {
            continue;
        }

        /**
         * if the command is exit, the loop is done.
         */
        if (0 == strncmp(argv2[0], "exit", 4))
        {
            break;
        }

        /**
         * if the last argument is '&' then the user wants to background the command.
         * set the 'background' variable to 1 to indicate this and remove the '&' from
         * the argument array (otherwise execve seems to try to interpret it...)
         */
        if (0 == strncmp("&", argv2[n -1], 1))
        {
            background = 1;
            argv2[n -1] = NULL;
        }

        /**
         * get the path to the binary that the user wants to execute by checking the 
         * PATH env variable. If get_command_path returns NULL, then use the exact
         * value input by the user.
         */
        filename = get_command_path(argv2[0], envp);
        if (filename)
        {
            argv2[0] = filename;
        }

        /**
         * fork a new process to execute the command.
         */
        child = fork();
        if (-1 == child)
        {
            exit(1); /* exit on error. */
        }

        /**
         * if this is the child process, call execve using argv2 and envp.
         * if execve fails, exit.
         */
        else if (0 == child)
        {
            if (-1 == execve(argv2[0], (const char *const *)argv2, (const char *const *) envp))
            {
                printstr(STDERR, "error: execve\n");
                free(filename);
                filename = NULL;
                exit(1);
            }
            /**
             * execve succeeds, but the command is invalid and returns here.
             */
            free(filename);
            filename = NULL;
            exit(1);
        }
        else
        {
            /**
             * wait for the child process unless the user wants to background it.
             */
            if (background)
            {
                goto reset;
            }
            if (-1 == waitpid(child, &status, __WALL))
            {
                printstr(STDERR, "error: waitpid\n");
                exit(1);
            }
        }

reset:
        /**
         * reset some variables for each iteration.
         */
        background = 0;
        memset(buff, 0, MAX_BUFF_LEN);
        free(filename);
        filename = NULL;
    }
    return 0;
}
