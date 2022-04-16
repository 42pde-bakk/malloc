//
// Created by Peer De bakker on 3/26/22.
//

#include "peer_stdlib.h"
#include <assert.h>

t_heap *allocateHeap(const size_t alloc_size) {
	assert(alloc_size % getpagesize() == 0);

	t_heap	*newHeap = mmap(NULL, alloc_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
	if (newHeap == MAP_FAILED)
		return (MAP_FAILED);
	newHeap->total_size = alloc_size;
	newHeap->block_count = 0;
	newHeap->prev = NULL;
	newHeap->next = NULL;

	block_init(ZONE_SHIFT(newHeap), alloc_size - sizeof(t_heap) - sizeof(t_block));
	return (newHeap);
}

t_heap *get_last_zone(t_heap *zone) {
	if (!zone)
		return (NULL);

	while (zone->next)
		zone = zone->next;
	return (zone);
}

void	heap_push_back(t_heap** heap, t_heap* new_heap) {
	t_heap* tmp = *heap;

	while (tmp->next) {
		tmp = tmp->next;
	}
	tmp->next = new_heap;
	new_heap->prev = tmp;
}

void	extend_heap(t_heap* heap, const size_t alloc_size) {
	t_heap* newHeap = allocateHeap(alloc_size);
	heap_push_back(&heap, newHeap);
}
