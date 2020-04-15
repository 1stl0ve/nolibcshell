/**
 * Dummy implementation of stdlib.
 * 
 * Provides SUPER simple "memory management" functions.
 */
#include <stdlib.h>
#include "syscall.h"

/**
 * danlulu.com/malloc-tutorial.
 */

void *g_heap_base = NULL;

typedef struct block_meta_t {
    size_t size;
    struct block_meta_t *next;
    int free;
    int magic;
} block_meta_t;

#define META_SIZE sizeof(block_meta_t)

block_meta_t *find_free_block(block_meta_t **last, size_t size)
{
    block_meta_t *current = g_heap_base;
    while (current && !(current->free && current->size >= size))
    {
        *last = current;
        current = current->next;
    }
    return current;
}

block_meta_t *request_space(block_meta_t *last, size_t size)
{
    block_meta_t *block = NULL;
    void *request = NULL;

    //block = (block_meta_t *)sys_brk(0);
    block = (block_meta_t *) (unsigned long) syscall1(SYSBRK, 0);
    //request = (void *)sys_brk((unsigned long) block + size + META_SIZE);
    unsigned long request_size = (unsigned long) size + (unsigned long) META_SIZE + (unsigned long)block;
    //request = (void *)(unsigned long) syscall1(SYSBRK, (unsigned long) block + size + META_SIZE);
    request = (void *)(unsigned long) syscall1(SYSBRK, request_size);
    if (request == (void *)-1)
    {
        return NULL;
    }

    if (last)
    {
        last->next = block;
    }
    block->size = size;
    block->next = NULL;
    block->free = 0;
    block->magic = 0x12345678;
    return block;
}

block_meta_t *get_block_ptr(void *ptr)
{
    return (block_meta_t *)ptr - 1;
}

void *malloc(size_t size)
{
    block_meta_t *block = NULL;
    block_meta_t *last = NULL;

    if (size <= 0) 
    {
        return NULL;
    }

    if (!g_heap_base)
    {
        block = request_space(NULL, size);
        if (!block)
        {
            return NULL;
        }
        g_heap_base = block;
    }
    else 
    {
        last = g_heap_base;
        block = find_free_block(&last, size);
        if (!block)
        {
            block = request_space(last, size);
            if (!block)
            {
                return NULL;
            }
        }
        else 
        {
            block->free = 0;
            block->magic = 0x77777777;
        }
    }

    return block + 1;
}

void free(void *ptr)
{
    block_meta_t *block = NULL;

    if (!ptr)
    {
        return;
    }

    block = get_block_ptr(ptr);
    if (block->free != 0)
    {
        return;
    }

    block->free = 1;
    block->magic = 0x55555555;
}

void exit(int status)
{
    syscall1(SYSEXIT, status);
    /* does not return. */
}