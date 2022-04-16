//
// Created by Peer De bakker on 2/14/22.
//

#include "peer_stdlib.h"
#include <stdio.h>


void	check(void* ptr) {
	printf("is ptr %p 16byte aligned?: %d\n", ptr, ((uintptr_t)ptr & 0xFu) == 0);
}


size_t	align_16bytes(const size_t size) {
	return (size + 15u) & ~0xFu;
}

bool	isTiny(const size_t size) {
	return (size <= TINY_BLOCK_SIZE);
}

bool	isSmall(const size_t size) {
	return (TINY_BLOCK_SIZE < size && size <= SMALL_BLOCK_SIZE);
}

bool	isLarge(const size_t size) {
	return (size > SMALL_BLOCK_SIZE);
}

static void	malloc_init(const size_t size) {
	if (!g_malloc_zones.tiny && isTiny(size)) {
		g_malloc_zones.tiny = allocateHeap(TINY_HEAP_ALLOCATION_SIZE);
	} else if (!g_malloc_zones.small && isSmall(size)) {
		g_malloc_zones.small = allocateHeap(SMALL_HEAP_ALLOCATION_SIZE);
	}
}

void*	find_spot_in_heaplist(t_heap* heap, size_t size, size_t heap_alloc_size) {
	while (heap) {
		t_block* block = ZONE_SHIFT(heap);
		printf("block starts at %p, next ptr is %p\n", (void*)block, (void*)block->next);
		printf("free: %d, size: %zu\n", block->free, block->data_size);
		while (block) {
//			printf("in blockloop\n");
			if (block->free && block->data_size >= size) {
				// We can re-use this block
				block->free = 0;
				check(block);
				check(BLOCK_SHIFT(block));
				printf("sizeof block = %zu\n", sizeof(t_block));
				return (BLOCK_SHIFT(block));
			}
			if (!block->next)
				break;
			block = block->next;
		}
		printf("couldnt find an empty spot\n");
		// Couldn't find a spot in our existing linked list of blocks, but maybe we can append a block?
		t_block *new_block = (t_block*)(block + block->data_size);
		if ((void*)(new_block + sizeof(t_block) + size) < (void*)(heap + heap->total_size)) {
			block_init(new_block, size);
			block->next = new_block;
			return (BLOCK_SHIFT(new_block));
		}
		if (!heap->next) {
			// extend zone
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
	const size_t oldsize = size;

	size = align_16bytes(size);
	printf("size went from %zu to %zu\n", oldsize, size);

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
	printf("malloc returns %p\n", result);
	check(result);
	return (result);
}
