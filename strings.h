#ifndef __STRINGS_H
#define __STRINGS_H

void zero_string(char *str, unsigned length);
int string_cmp(char *str1, char *str2, unsigned length);
int string_length(char *str);
char *string_tok(char *str, char del);

#endif
