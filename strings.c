#include "strings.h"

void zero_string(char *str, unsigned length)
{
    int i = 0;
    for (i = 0; i < length; i++)
    {
        str[i] = 0;
    }
}

int string_cmp(char *str1, char *str2, unsigned length)
{
    int i = 0;
    for (i = 0; i < length; i++)
    {
        if (str1[i] != str2[i])
        {
            return -1;
        }
    }
    return 0;
}

int string_length(char *str)
{
    int i = 0;
    char *pos = 0;

    if (!str)
    {
        return 0;
    }

    for (pos = str; *pos != '\0'; pos++)
    {
        i++;
    }
    return i;
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