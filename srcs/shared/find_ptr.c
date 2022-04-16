//
// Created by Peer De bakker on 4/16/22.
//

#include "peer_stdlib.h"

t_block*	loop_blocks(t_block* block, void* ptr, bool remove) {
	t_block	*prev = NULL;

	while (block) {
		if (BLOCK_SHIFT(block) == ptr) {
			if (remove) {
				prev->next = block->next;
				block->next = NULL;
			}
			return (block);
		}
		prev = block;
		block = block->next;
	}
	return (NULL);
}

t_block*	loop_heap(t_heap* heap, void* ptr) {
	t_block	*result = NULL;

	while (heap) {
		if ((result = loop_blocks(ZONE_SHIFT(heap), ptr, false)))
			return (result);
		heap = heap->next;
	}
	return (NULL);
}
