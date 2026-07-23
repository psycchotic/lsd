#include <allocator/kmalloc.h>
#include <utils/memory.h>
#include <utils/printk.h>

void *kmalloc(size_t size) {
  size_t total = sizeof(kmalloc_header_t) + size;
  size_t pages = DIV_CEIL(total, PAGE_SIZE);

  void *mem = pmm_allocate_pages(pages);

  kmalloc_header_t *hdr = mem;
  hdr->pages = pages;
  hdr->size = size;

  return (void *)(hdr + 1);
}

void *kzalloc(size_t size) {
  void *a = kmalloc(size);
  if (a)
    memset(a, 0, size);

  return a;
}

void kfree(void *ptr) {
  if (!ptr)
    return;

  kmalloc_header_t *hdr = (kmalloc_header_t *)ptr - 1;

  pmm_free_pages((pmm_node_t *)hdr, hdr->pages);
}

void *krealloc(void *block, size_t size) {
  if (block == NULL)
    return kmalloc(size);

  if (size == 0) {
    kfree(block);
    return NULL;
  }

  kmalloc_header_t *hdr = (kmalloc_header_t *)block - 1;

  size_t old_size = hdr->size;

  size_t usable = hdr->pages * PAGE_SIZE - sizeof(kmalloc_header_t);

  if (size <= usable) {
    hdr->size = size;
    return block;
  }

  void *new_block = kmalloc(size);
  if (!new_block)
    return NULL;

  memcpy(new_block, block, old_size < size ? old_size : size);

  kfree(block);

  return new_block;
}
