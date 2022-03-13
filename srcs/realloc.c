//
// Created by Peer De bakker on 2/14/22.
//

#include "peer_stdlib.h"
#include "libc.h"
#include <stdio.h>

t_category get_category(const size_t size) {
	if (size == 0)
		return (ZERO);
	if (size <= TINY_BLOCK_SIZE)
		return (TINY);
	if (size <= SMALL_BLOCK_SIZE)
		return (SMALL);
	return (LARGE);
}

static bool is_same_category(const size_t a, const size_t b) {
	return (get_category(a) == get_category(b));
}

void	*realloc(void *ptr, size_t size) {
	if (!ptr)
		return (malloc(size));

	t_zone* zone = check_smaller_zones(ptr);
	if (!zone) {
		// ptr is not in TINY or SMALL
		zone = check_large_zone_ll(ptr);
		if (zone)
			return (BLOCK_SHIFT(ZONE_SHIFT(zone)));
		return (NULL);
	}
	t_block* block = find_block(ptr, zone);
	if (!block) // Invalidly aligned pionter
		return (NULL);
	if (size == block->data_size || (size < block->data_size && is_same_category(size, block->data_size))) {
		printf("yo we in here\n");
		return (ptr);
	}
	t_block	*newblock = find_spot(size);
	if (!newblock) // It is not freed if realloc fails to obtain a large enough block of memory and returns NULL.
		return (NULL);
	void *new_ptr = ft_memcpy(BLOCK_SHIFT((void*)newblock), BLOCK_SHIFT((void*)block), block->data_size);
	printf("newblock: %p (%p), %zu, %d\n", (void*)newblock, BLOCK_SHIFT(newblock), newblock->data_size, newblock->status);

	release_block(block, zone);
	return (new_ptr);
}
