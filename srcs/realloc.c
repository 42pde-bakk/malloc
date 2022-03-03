//
// Created by Peer De bakker on 2/14/22.
//

#include "peer_stdlib.h"
#include "libc.h"

void *realloc(void *ptr, size_t size) {
	if (!ptr)
		return (malloc(size));

	t_zone* zone = find_zone(ptr);
	if (!zone)// ptr is in a different page than my allocated zones
		return (NULL);
	t_block* block = find_block(ptr, zone);
	if (!block) // Invalidly aligned pionter
		return (NULL);
	if (size > block->data_size) {
		t_block	*newblock = find_spot(size);
		if (!newblock) // It is not freed if realloc fails to obtain a large enough block of memory and returns NULL.
			return (NULL);
		free(block); // if realloc() returns a pointer to a different location, the old location is freed.
		return (ft_memcpy(BLOCK_SHIFT((void*)newblock), BLOCK_SHIFT((void*)block), block->data_size));
	} else if (size < block->data_size) {
		return (ptr); // do I need to create a new block with less range?
	}
	// If size == block->size, No operation

    return (ptr);
}
