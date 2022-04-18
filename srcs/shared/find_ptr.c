//
// Created by Peer De bakker on 4/16/22.
//

#include "malloc_internal.h"

t_block*	loop_blocks(t_block* block, void* ptr, bool remove) {
	while (block) {
		if (BLOCK_SHIFT(block) == ptr) {
			if (remove)
				remove_block_from_list(block);
			return (block);
		}
		block = block->next;
	}
	return (NULL);
}

void *loop_heap(t_heap* heap, void* ptr, loop_func func) {
	t_block	*result = NULL;

	while (heap) {
		if ((result = loop_blocks(ZONE_SHIFT(heap), ptr, false))) {
			return (func(heap, result));
		}
		heap = heap->next;
	}
	return (NULL);
}
