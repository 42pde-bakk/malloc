//
// Created by Peer De bakker on 2/14/22.
//

#include "malloc_internal.h"
#include "libc.h"

static void	error_realloc(void *ptr) {
	ft_putstr_fd("malloc *** error for object ", STDERR_FILENO);
	ft_putnbr_base_fd((unsigned long long int) ptr, 16, STDERR_FILENO);
	ft_putstr_fd(": pointer being realloc'd was not allocated\n", STDERR_FILENO);
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
		if ((result = loop_blocks(HEAP_SHIFT(heap), ptr))) {
			return (realloc_check(result, heap, size));
		}
		heap = heap->next;
	}
	return (NULL);
}

void	*realloc_large(void *ptr, size_t size) {
	void *malloc_ret;
	t_block	*block = loop_blocks(g_malloc_zones.large, ptr);

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
	t_block	*result = NULL;

	if (!ptr)
		return (malloc_internal(size));

	size = align_16bytes(size);
	if ((result = realloc_loop_heap(g_malloc_zones.tiny, ptr, size))) {
		return (result);
	}
	if ((result = realloc_loop_heap(g_malloc_zones.small, ptr, size))) {
		return (result);
	}
	if ((result = realloc_large(ptr, size))) {
		return (result);
	}
	if (DEBUG_FAULTY_POINTERS)
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
