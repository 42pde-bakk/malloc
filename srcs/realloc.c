//
// Created by Peer De bakker on 2/14/22.
//

#include "malloc_internal.h"
#include "libc.h"
#include <stdio.h>

static void	error_realloc(void *ptr) {
	dprintf(2, "malloc *** error for object %p: pointer being realloc'd was not allocated\n", ptr);
	dprintf(2, "malloc: *** set a breakpoint in malloc_error_break to debug\n");
}

void*	realloc_check(t_block* block, t_heap* heap, size_t size) {
	void *malloc_ret;

	if (size > block->data_size) {
		// gotta realloc
		malloc_ret = malloc_internal(size);
		ft_memcpy(malloc_ret, BLOCK_SHIFT(block), block->data_size);
		free_block(heap, block);
		return (malloc_ret);
	}
	else if (!isSameCategory(size, block->data_size)) {
		// gonna put the new allocation in a different size category, so also gotta realloc
		malloc_ret = malloc_internal(size);
		ft_memcpy(malloc_ret, BLOCK_SHIFT(block), size);
		free_block(heap, block);
		return (malloc_ret);
	}
	// seems like we have enough space to just leave the allocation as is
	return (BLOCK_SHIFT(block));
}

void *realloc_loop_heap(t_heap* heap, void* ptr, size_t size) {
	t_block	*result = NULL;

	while (heap) {
		if ((result = loop_blocks(ZONE_SHIFT(heap), ptr, false))) {
			return (realloc_check(result, heap, size));
		}
		heap = heap->next;
	}
	return (NULL);
}

void	*realloc_large(void *ptr, size_t size) {
	void *malloc_ret;
	t_block	*block = loop_blocks(g_malloc_zones.large, ptr, false);

	if (!block)
		return (NULL);
	if (size > block->data_size) {
		// gotta realloc
		malloc_ret = malloc_internal(size);
		ft_memcpy(malloc_ret, BLOCK_SHIFT(block), block->data_size);

		if (g_malloc_zones.large == block) // update head pointer if needed
			g_malloc_zones.large = block->next;
		remove_block_from_list(block);
		munmap((void *)block, block->data_size);
		return (malloc_ret);
	} else if (!isLarge(size)) {
		// gonna put the new allocation in a different size category, so also gotta realloc
		malloc_ret = malloc_internal(size);
		ft_memcpy(malloc_ret, BLOCK_SHIFT(block), size);
		if (g_malloc_zones.large == block) // update head pointer
			g_malloc_zones.large = block->next;
		remove_block_from_list(block);
		munmap((void *)block, block->data_size);
		return (malloc_ret);
	}
	return (BLOCK_SHIFT(block));
}

void	*realloc_internal(void *ptr, size_t size) {
	size = align_16bytes(size);
	if (!ptr)
		return (malloc_internal(size));

	t_block	*result = NULL;
	if ((result = realloc_loop_heap(g_malloc_zones.tiny, ptr, size))) {
		return (result);
	}
	if ((result = realloc_loop_heap(g_malloc_zones.small, ptr, size))) {
		return (result);
	}
	if ((result = realloc_large(ptr, size))) {
		return (result);
	}
	error_realloc(ptr);
	return (NULL);
}

void	*realloc(void *ptr, size_t size) {
	void *res;

	pthread_mutex_lock(&g_mutex);
	res = realloc_internal(ptr, size);
	pthread_mutex_unlock(&g_mutex);
	return (res);
}

//void *realloc(void *ptr, size_t size) {
//	if (!ptr)
//		return (malloc(size));
//
//	pthread_mutex_lock(&g_mutex);
//	t_heap* zone = check_smaller_zones(ptr);
//	if (!zone) {
//		// ptr is not in TINY or SMALL
//		zone = check_large_zone_ll(ptr);
//		pthread_mutex_unlock(&g_mutex);
//		if (zone)
//			return (ZONE_SHIFT(zone));
//		return (NULL);
//	}
//	t_block* block = find_block(ptr, zone);
//	if (!block) { // Invalidly aligned pionter
//		pthread_mutex_unlock(&g_mutex);
//		return (NULL);
//	}
//	if (size > block->data_size) {
//		t_block	*newblock = find_spot(size);
//		if (!newblock) { // It is not freed if realloc fails to obtain a large enough block of memory and returns NULL.
//			pthread_mutex_unlock(&g_mutex);
//			return (NULL);
//		}
//		void *new_ptr = ft_memcpy(BLOCK_SHIFT((void*)newblock), BLOCK_SHIFT((void*)block), block->data_size);
//		free(block); // if realloc() returns a pointer to a different location, the old location is freed.
//		pthread_mutex_unlock(&g_mutex);
//		return (new_ptr);
//	} else if (size < block->data_size) {
//		pthread_mutex_unlock(&g_mutex);
//		return (ptr); // do I need to create a new block with less range?
//	}
//	// If size == block->size, No operation
//	pthread_mutex_unlock(&g_mutex);
//    return (ptr);
//}
