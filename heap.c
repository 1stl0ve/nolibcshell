/**
 * Dummy implementation of heap.
 * 
 * Provides SUPER simple "memory management" functions.
 */
#include "mylib.h"
#include "syscall.h"

/**
 * This code is base on the tutorial found at: danlulu.com/malloc-tutorial.
 */

#define META_SIZE sizeof(block_meta_t)

void *g_heap_base = NULL;

/**
 * block_meta_t:
 * @brief a structure to represent a heap block's metadata.
 * 
 * This structure tracks a block's size, what the next block in the heap is, and whether
 * or not this block is free to be re-used.
 */
typedef struct __attribute__((packed)) block_meta_t
{
    size_t size;
    struct block_meta_t *next;
    int free;
    int magic;
} block_meta_t;

/**
 * find_free_block:
 * @brief returns a pointer to the next free block.
 * 
 * This function iterates through the heap and returns the next free block.
 * 
 * @param last - the previous block.
 * @param size - the number of bytes to request.
 * @return a pointer to a free block; NULL if there are not any large enough blocks.
 */
static block_meta_t *find_free_block(block_meta_t **last, size_t size)
{
    block_meta_t *current = g_heap_base;
    while (current && !(current->free && current->size >= size))
    {
        *last = current;
        current = current->next;
    }
    return current;
}

/**
 * request_space:
 * @brief requests more space on the heap.
 * 
 * @param last - the last heap base.
 * @param size - the number of bytes to request.
 * @return a pointer to the new block; NULL on error.
 */
static block_meta_t *request_space(block_meta_t *last, size_t size)
{
    block_meta_t *block = NULL;
    void *request = NULL;
    unsigned long request_size = 0;

    block = (block_meta_t *)(unsigned long)syscall1(SYSBRK, 0);
    request_size = (unsigned long)size + (unsigned long)META_SIZE + (unsigned long)block;
    request = (void *)(unsigned long)syscall1(SYSBRK, request_size);
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

/**
 * get_block_ptr:
 * @brief gets a pointer to a block's metadata.
 * 
 * @param ptr - a pointer to a memory address.
 * @return a pointer to the metadata for the block of memory.
 */
static block_meta_t *get_block_ptr(void *ptr)
{
    return (block_meta_t *)ptr - 1;
}

/**
 * malloc:
 * @brief dynamically allocates a specified number of bytes on the heap.
 * 
 * @param size - the number of bytes to request.
 * @return a pointer to the allocated block; NULL on error.
 */
void *malloc(size_t size)
{
    block_meta_t *block = NULL;
    block_meta_t *last = NULL;

    /**
     * do not allocate 0 bytes.
     */
    if (size <= 0)
    {
        return NULL;
    }

    /**
    * if this is the first allocation, request for initial heap space.
    */
    if (!g_heap_base)
    {
        block = request_space(NULL, size);
        if (!block)
        {
            return NULL;
        }
        g_heap_base = block;
    }

    /** 
     * check to see if there is a free block with enough space for the new allocation.
     */
    else
    {
        last = g_heap_base;
        block = find_free_block(&last, size);

        /**
         * if there aren't any free blocks, request more space.
         */
        if (!block)
        {
            block = request_space(last, size);
            if (!block)
            {
                return NULL;
            }
        }

        /**
         * if a block is found, mark it as in use.
         */
        else
        {
            block->free = 0;
            block->magic = 0x77777777;
        }
    }

    /**
     * when returning the pointer, be sure to skip the metadata.
     */
    return block + 1;
}

/**
 * free:
 * @brief marks a block as free for future use.
 * 
 * @param ptr - a pointer to a heap block.
 * @return void.
 */
void free(void *ptr)
{
    block_meta_t *block = NULL;

    /**
     * if the pointer is NULL, don't do anything. 
     * (I'm not sure why the libc implementation of free() doesn't do this...)
     */
    if (!ptr)
    {
        return;
    }

    /**
     * Get the block metadata.
     */
    block = get_block_ptr(ptr);
    if (block->free != 0)
    {
        return;
    }

    /**
     * mark this block as free for future use.
     */
    block->free = 1;
    block->magic = 0x55555555;
}
