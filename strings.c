#include <stdlib.h>

#include "strings.h"

void zero_string(char *str, unsigned length)
{
    int i = 0;
    for (i = 0; i < length; i++)
    {
        str[i] = 0;
    }
}

int strncmp(const char *s1, const char *s2, size_t n)
{
    int i = 0;
    for (i = 0; i < n; i++)
    {
        if (s1[i] != s2[i])
        {
            return -1;
        }
    }
    return 0;
}

size_t strlen(const char *s)
{
    size_t i = 0;
    char *pos = (char *)s;

    if (!pos)
    {
        return 0;
    }

    for (; *pos != '\0'; pos++)
    {
        i++;
    }
    return i;
}

char *strncpy(char *dest, const char *src, size_t n)
{
    size_t i = 0;

    /* copy up to n bytes or until null byte. */
    for (i = 0; i < n && src[i] != '\0'; i++)
    {
        dest[i] = src[i];
    }

    /* zero out the rest. */
    for (; i < n; i++)
    {
        dest[i] = '\0';
    }

    return dest;
}

void *memcpy(void *dest, const void *src, size_t n)
{
    size_t i = 0;

    /* copy n bytes. */
    for (i = 0; i < n; i++)
    {
        ((char *)dest)[i] = ((char *)src)[i];
    }
    return dest;
}

char *string_tok(char *str, char del)
{
    int i = 0;
    for (i = 0; str[i] != del && str[i] != '\0'; i++) {}

    if (str[i] == '\0')
    {
        return 0;
    }

    str[i++] = '\0';
    return str + i;
}

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