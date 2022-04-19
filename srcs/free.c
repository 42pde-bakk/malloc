//
// Created by Peer De bakker on 2/14/22.
//

#include "malloc_internal.h"
#include <stdio.h>
#include <assert.h>

static void	error_free(void *ptr) {
	dprintf(2, "malloc *** error for object %p: pointer being freed was not allocated\n", ptr);
//	dprintf(2, "malloc: *** set a breakpoint in malloc_error_break to debug\n");
}

void	release_zone(t_heap *zone) {
	if (zone->prev)
		zone->prev->next = zone->next;
	if (zone->next)
		zone->next->prev = zone->prev;
	int ret = munmap((void *)zone, zone->total_size);
	if (ret) {
		// TODO: remove
		perror("munmap");
		dprintf(2, "tried to call munmap(%p, %zu)\n", (void*)zone, zone->total_size);
		assert(0);
	}
}

void*	free_block(t_heap* heap, t_block* block) {
//	dprintf(2, "in free_block: block->free = %d\n", block->free);
	if (block->free)
		return (NULL);
	block->free = 1;
	assert(heap->block_count > 0);
	heap->block_count--;
//	dprintf(2, "heap->block_count = %zu\n", heap->block_count);
	return (heap);
}

// not locking the mutex here
int free_internal(void* ptr) {
	void	*result = NULL;
	if ((result = loop_heap(g_malloc_zones.tiny, ptr, free_block))) {
		t_heap	*heap = (t_heap *)result;
		if (heap->block_count == 0 && (heap->prev || heap->next)) {
			if (g_malloc_zones.tiny == heap)
				g_malloc_zones.tiny = heap->next;
			remove_heap_from_list(heap);
			release_heap(heap);
		}
		return (0);
	}
	if ((result = loop_heap(g_malloc_zones.small, ptr, free_block))) {
		t_heap	*heap = (t_heap *)result;
		if (heap->block_count == 0 && (heap->prev || heap->next)) {
			if (g_malloc_zones.small == heap)
				g_malloc_zones.small = heap->next;
			remove_heap_from_list(heap);
			release_heap(heap);
		}
		return (0);
	}
	if ((result = loop_blocks(g_malloc_zones.large, ptr))) {
		t_block	*block = (t_block *)result;
		assert(block != block->next);
		if (g_malloc_zones.large == block)
			g_malloc_zones.large = block->next;
		remove_block_from_list(block);
		if (block->prev)
			assert(block->prev != block->prev->next);
		if (block->next)
			assert(block->next != block->next->prev);
		assert(g_malloc_zones.large != block);
		if (munmap(block, block->data_size))
			perror("munmap large");
		return (0);
	}
	error_free(ptr);
	return (1);
}

void    free(void* ptr) {
	if (!ptr)
		return ;

	pthread_mutex_lock(&g_mutex);
	if (g_log)
		dprintf(2, "calling free(%p)\n", ptr);
	if (free_internal(ptr)) {
		pthread_mutex_unlock(&g_mutex);
		return ;
	}
	if (g_log)
		dprintf(2, "freed %p\n", ptr);
	pthread_mutex_unlock(&g_mutex);
}
