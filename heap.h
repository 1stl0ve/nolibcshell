#ifndef __STDLIB_H
#define __STDLIB_H

#define NULL 0

typedef unsigned long long size_t;

void *malloc(size_t size);
void free(void *ptr);
void exit(int status);

#endif
