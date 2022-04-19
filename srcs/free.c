//
// Created by Peer De bakker on 2/14/22.
//

#include "malloc_internal.h"
#include <stdio.h>
#include <assert.h>
#include <libc.h>

void	error_free(void *ptr) {
	ft_putstr_fd("malloc *** error for object ", STDERR_FILENO);
	ft_putnbr_base_fd((unsigned long long int) ptr, 16, STDERR_FILENO);
	ft_putstr_fd(": pointer being freed was not allocated\n", STDERR_FILENO);
}

void	release_zone(t_heap *zone) {
	if (zone->prev)
		zone->prev->next = zone->next;
	if (zone->next)
		zone->next->prev = zone->prev;
	if (munmap((void *)zone, zone->total_size)) {
		ft_putstr_fd("munmap failed\n", STDERR_FILENO);
	}
}

void*	free_block(t_heap* heap, t_block* block) {
	if (block->free)
		return (NULL);
	block->free = 1;
	heap->block_count--;
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
//		assert(block != block->next);
		if (g_malloc_zones.large == block)
			g_malloc_zones.large = block->next;
		remove_block_from_list(block);
//		if (block->prev)
//			assert(block->prev != block->prev->next);
//		if (block->next)
//			assert(block->next != block->next->prev);
//		assert(g_malloc_zones.large != block);
		if (munmap(block, block->data_size))
			ft_putstr_fd("munmap failed\n", 2);
		return (0);
	}
	// error_free(ptr);
	return (1);
}

void    free(void* ptr) {
	if (!ptr)
		return ;

	pthread_mutex_lock(&g_mutex);
	free_internal(ptr);
	pthread_mutex_unlock(&g_mutex);
}
