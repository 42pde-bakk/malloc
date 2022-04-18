//
// Created by Peer De bakker on 2/14/22.
//

#include "malloc_internal.h"
#include <stdio.h>


static void	malloc_init(const size_t size) {
	if (!g_malloc_zones.tiny && isTiny(size)) {
		g_malloc_zones.tiny = allocateHeap(TINY_HEAP_ALLOCATION_SIZE);
		t_block *first = ZONE_SHIFT(g_malloc_zones.tiny);
		first->data_size = (size_t)-1;
	} else if (!g_malloc_zones.small && isSmall(size)) {
		g_malloc_zones.small = allocateHeap(SMALL_HEAP_ALLOCATION_SIZE);
		t_block *first = ZONE_SHIFT(g_malloc_zones.small);
		first->data_size = (size_t)-1;
	}
}

void*	find_spot_in_heaplist(t_heap* heap, size_t size, size_t heap_alloc_size) {
	while (heap) {
//		dprintf(2, "checking heap %p\n", (void*)heap);
		t_block* block = ZONE_SHIFT(heap);
//		dprintf(2, "got block\n");
		while (block) {
			if (block->data_size == (size_t)-1 || (block->free && block->data_size >= size)) {
				// We can re-use this block
//				check(block);
//				check(BLOCK_SHIFT(block));
//				printf("sizeof block = %zu\n", sizeof(t_block));
				block->free = 0;
				if (block->data_size == (size_t)-1)
					block->data_size = size;

				heap->block_count++;
				return (BLOCK_SHIFT(block));
			}
			if (!block->next)
				break;
			block = block->next;
		}
		// Couldn't find a spot in our existing linked list of blocks, but maybe we can append a block?
		t_block *new_block = (t_block*)(block + block->data_size);
		void	*block_end = (void *)new_block + sizeof(t_block) + size;
		void	*heap_end = (void *)heap + heap->total_size;
		if (block_end < heap_end) {
			block_init(new_block, size);
			block->next = new_block;
			return (BLOCK_SHIFT(new_block));
		}
		if (!heap->next) {
			// extend zone
//			dprintf(2, "lets extend the heap\n");
			extend_heap(heap, heap_alloc_size);
		}
		heap = heap->next;
	}
	return (NULL);
}

void	*large_malloc(const size_t size) {
	void	*ret;
	t_block	*block;
	const size_t total_size = size + sizeof(t_block);

	ret = allocateHeap(total_size);
	block = (t_block*)ret;
	block_init(block, size);
	if (!g_malloc_zones.large)
		g_malloc_zones.large = block;
	else
		block_push_back(&g_malloc_zones.large, block);
	return BLOCK_SHIFT(block);
}

void	*malloc_internal(size_t size) {
	void	*result;

	size = align_16bytes(size);
	malloc_init(size);

	if (size <= TINY_BLOCK_SIZE) {
		result = find_spot_in_heaplist(g_malloc_zones.tiny, size, TINY_HEAP_ALLOCATION_SIZE);
	} else if (size <= SMALL_BLOCK_SIZE) {
		result = find_spot_in_heaplist(g_malloc_zones.small, size, SMALL_HEAP_ALLOCATION_SIZE);
	} else {
		result = large_malloc(size);
	}
	return (result);
}

void* malloc(size_t size) {
	void	*result;

	pthread_mutex_lock(&g_mutex);
	result = malloc_internal(size);
	pthread_mutex_unlock(&g_mutex);
//	printf("malloc returns %p\n", result);
//	check(result);
	return (result);
}
