#ifndef __STRINGS_H
#define __STRINGS_H

void zero_string(char *str, unsigned length);
int strncmp(const char *s1, const char *s2, size_t n);
size_t strlen(const char *s);
char *strncpy(char *dest, const char *src, size_t n);
void *memcpy(void *dest, const void *src, size_t n);
void *memset(void *s, int c, size_t n);
char *string_tok(char *str, char del);

#endif
