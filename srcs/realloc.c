//
// Created by Peer De bakker on 2/14/22.
//

#include "peer_stdlib.h"
#include "libc.h"
#include <stdio.h>

void *realloc(void *ptr, size_t size) {
	if (!ptr)
		return (malloc(size));

	t_zone* zone = check_smaller_zones(ptr);
	if (!zone) {
		// ptr is not in TINY or SMALL
		zone = check_large_zone_ll(ptr);
		if (zone)
			return (ZONE_SHIFT(zone));
		return (NULL);
	}
	t_block* block = find_block(ptr, zone);
	if (!block) // Invalidly aligned pionter
		return (NULL);
	if (size > block->data_size) {
		t_block	*newblock = find_spot(size);
		if (!newblock) // It is not freed if realloc fails to obtain a large enough block of memory and returns NULL.
			return (NULL);
		void *new_ptr = ft_memcpy(BLOCK_SHIFT((void*)newblock), BLOCK_SHIFT((void*)block), block->data_size);
		free(block); // if realloc() returns a pointer to a different location, the old location is freed.
		return (new_ptr);
	} else if (size < block->data_size) {
		return (ptr); // do I need to create a new block with less range?
	}
	// If size == block->size, No operation

    return (ptr);
}
