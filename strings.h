#ifndef __STRINGS_H
#define __STRINGS_H

/**
 * @brief checks each value in a string for equality.
 */
int strncmp(const char *s1, const char *s2, size_t n);

/**
 * @brief returns the number of bytes in a string (excluding the terminating NULL byte).
 */
size_t strlen(const char *s);

/**
 * @brief copies up to n bytes from one pointer to another.
 */
char *strncpy(char *dest, const char *src, size_t n);

/**
 * @brief tokenizes a string on a given delimeter.
 */
char *strtok(char *str, char del);

/**
 * @brief sets a range of addresses to a given value.
 */
void *memset(void *s, int c, size_t n);

/**
 * @brief a wrapper function for calling the write syscall on a string.
 */
void printstr(int fd, char *str);

#endif
