#ifndef KMALLOC_H_
#define KMALLOC_H_

#include <allocator/pmm.h>

typedef struct kmalloc_header {
  size_t pages;
  size_t size;
} kmalloc_header_t;

void *kmalloc(size_t size);
void kfree(void *block);

void *kzalloc(size_t size);
void *krealloc(void *block, size_t size);

#endif
