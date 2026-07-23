#ifndef PMM_H_
#define PMM_H_
#include <limine/requests.h>
#include <stddef.h>
#include <stdint.h>
#define DIV_CEIL(a, b) (((a) + (b) - 1) / (b))
#define PAGE_SIZE 4096
static inline uintptr_t pmm_phys_to_virt(uintptr_t phys) {
  return phys + hhdm_request.response->offset;
}
static inline uintptr_t pmm_virt_to_phys(uintptr_t virt) {
  return virt - hhdm_request.response->offset;
}
// a PMM implemented as a free list
typedef struct pmm_node {
  // VIRTUAL address of the next node
  struct pmm_node *next;
} pmm_node_t;
pmm_node_t *pmm_get_head();
void pmm_map_pages();
void pmm_map_acpi_pages();
void pmm_map_bootloader_pages();
pmm_node_t *pmm_allocate_page();
pmm_node_t *pmm_allocate_pages(size_t count);
void pmm_free_page(pmm_node_t *node);
void pmm_free_pages(pmm_node_t *node, size_t count);
uint64_t pmm_total_entries();
void pmm_init();
#endif
