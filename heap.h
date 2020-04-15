#ifndef __STDLIB_H
#define __STDLIB_H

/**
 * @brief dynamically allocates a specified number of bytes on the heap.
 */ 
void *malloc(size_t size);
 
/**
 * @brief marks a block as free for future use.
 */
void free(void *ptr);

#endif
