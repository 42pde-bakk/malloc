//
// Created by Peer De bakker on 4/16/22.
//

#include "malloc_internal.h"

t_block*	loop_blocks(t_block* block, void* ptr) {
	while (block) {
		if (BLOCK_SHIFT(block) == ptr) {
			return (block);
		}
		block = block->next;
	}
	return (NULL);
}

void *loop_heap(t_heap* heap, void* ptr, loop_func func) {
	t_block	*result = NULL;

	while (heap) {
		if ((result = loop_blocks(ZONE_SHIFT(heap), ptr))) {
			return (func(heap, result));
		}
		heap = heap->next;
	}
	return (NULL);
}
