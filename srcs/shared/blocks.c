//
// Created by Peer De bakker on 3/1/22.
//

#include "peer_stdlib.h"

static size_t  block_get_available_space(const t_block* block, const void* zone_end) {
	void* block_data = BLOCK_SHIFT((void *)block);

	if (block->next)
		return ((void *)block->next - block_data);
	return (zone_end - block_data);
}

int check_block(const t_block* block, const size_t size, t_zone* zone) {
	if (block->status == ALLOCATED)
		return (0);

	return (size <= block_get_available_space(block, (void *) zone + TINY_HEAP_ALLOCATION_SIZE));
}

t_block	*init_block(t_block* block, const size_t size, t_zone* zone) {
	block->status = ALLOCATED;
	block->data_size = size;
	++zone->block_count;
	return (block);
}

void	release_block(t_block* block, t_zone* zone) {
	block->status = FREED;
	--zone->block_count;
}

t_block	*find_block(void *ptr, t_zone *zone) {
	t_block	*block = ZONE_SHIFT((void *)zone);

	for (; block != NULL; block = block->next) {
		if (ptr == BLOCK_SHIFT((void *)block)) {
			return (block);
		}
	}
	return (NULL);
}
