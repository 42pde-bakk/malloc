//
// Created by Peer De bakker on 3/26/22.
//

#include "malloc_internal.h"
#include <libc.h>

t_heap *allocateHeap(size_t alloc_size) {
	size_t	real = PAGE_SIZE;
	while (alloc_size > real)
		real += PAGE_SIZE;

	if (alloc_size > get_rlimit_data())
		return (NULL);
	t_heap	*newHeap = mmap(NULL, real, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
	if (newHeap == MAP_FAILED)
		return (NULL);
	newHeap->total_size = real;
	newHeap->block_count = 0;
	newHeap->prev = NULL;
	newHeap->next = NULL;

	block_init(ZONE_SHIFT(newHeap), -1, 0);
	return (newHeap);
}

t_heap *get_last_zone(t_heap *zone) {
	if (!zone)
		return (NULL);

	while (zone->next)
		zone = zone->next;
	return (zone);
}

void	heap_push_back(t_heap **heap, t_heap *new_heap) {
	t_heap	*tmp = *heap;

	while (tmp->next) {
		tmp = tmp->next;
	}
	tmp->next = new_heap;
	new_heap->prev = tmp;
}

void	extend_heap(t_heap* heap, const size_t alloc_size) {
	t_heap	*newHeap = allocateHeap(alloc_size);
	if (newHeap)
		heap_push_back(&heap, newHeap);
}

void remove_heap_from_list(t_heap *heap) {
	if (heap->prev)
		heap->prev->next = heap->next;
	if (heap->next)
		heap->next->prev = heap->prev;
}

void	release_heap(t_heap *heap) {
	if (munmap((void *)heap, heap->total_size))
		ft_putstr_fd("munmap in free_block\n", 2);
}
