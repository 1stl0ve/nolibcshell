/**
 * A collection of useful string functions.
 * 
 * NOTE: all of these functions assume a properly formed C string with a terminating
 * NULL byte.
 * 
 */
#include "mylib.h"
#include "strings.h"
#include "syscall.h"

/**
 * strncmp:
 * @brief checks each value in a string for equality.
 * 
 * This function compares up to n bytes of two strings and checks if each value is equal.
 * 
 * @param s1 - string one.
 * @param s2 - string two.
 * @param n  - the number of bytes to compare.
 * @return 0 if s1 == s2; -1 otherwise.
 */
int strncmp(const char *s1, const char *s2, size_t n)
{
    size_t i = 0;
    for (i = 0; i < n; i++)
    {
        if (s1[i] != s2[i])
        {
            return -1;
        }
    }
    return 0;
}

/**
 * strlen:
 * @brief returns the number of bytes in a string (excluding the terminating NULL byte).
 * 
 * @param s - the string
 * @return the number of bytes in s.
 */
size_t strlen(const char *s)
{
    size_t i = 0;
    char *pos = (char *)s;

    /**
     * a NULL string has no length.
     */
    if (!pos)
    {
        return 0;
    }

    /**
     * count bytes until we find a '\0'.
     */
    for (; *pos != '\0'; pos++)
    {
        i++;
    }
    return i;
}

/**
 * strncpy:
 * @brief copies up to n bytes from one pointer to another.
 * 
 * @param dest - the destination pointer
 * @param src  - the source pointer
 * @param n    - the number of bytes to copy.
 * @return a pointer to dest.
 */
char *strncpy(char *dest, const char *src, size_t n)
{
    size_t i = 0;

    /**
     * copy up to n bytes or until null byte. 
     */
    for (i = 0; i < n && src[i] != '\0'; i++)
    {
        dest[i] = src[i];
    }

    /**
     * zero out the rest. 
     */
    for (; i < n; i++)
    {
        dest[i] = '\0';
    }

    return dest;
}

/**
 * strtok:
 * @brief tokenizes a string on a given delimeter.
 * 
 * NOTE: this function varies from the libc strtok in a number of ways:
 * (1) it takes a char delimeter,
 * (2) it does not track a pointer globally and
 * (3) it returns the next occurrence, not the first.
 * 
 * @param str - the string to tokenize.
 * @param del - a character to serve as the delimeter.
 * @return a pointer to one byte beyond the next delimeter; NULL if none is found.
 */
char *strtok(char *str, char del)
{
    int i = 0;
    for (i = 0; str[i] != del && str[i] != '\0'; i++) {}

    if (str[i] == '\0')
    {
        return NULL;
    }

    str[i++] = '\0';
    return str + i;
}

/**
 * memset:
 * @brief sets a range of addresses to a given value.
 * 
 * @param s - a pointer to the start of the range.
 * @param c - the value to set the memory to.
 * @param n - the number of bytes to set.
 * @return a pointer to the start of the range.
 */
void *memset(void *s, int c, size_t n)
{
    char *ptr = s;
    unsigned int i = 0;

    for (i = 0; i < n; i++)
    {
        ptr[i] = c;
    }

    return (void *)ptr;
}

/**
 * printstr:
 * @brief a wrapper function for calling the write syscall on a string.
 * 
 * @param fd - the file descriptor to write to.
 * @param str - the string to print.
 * @return void.
 */
void printstr(int fd, char *str)
{
    size_t len = strlen(str);
    syscall3(SYSWRITE, fd, str, len);
}
