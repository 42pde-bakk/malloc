//
// Created by Peer De bakker on 3/1/22.
//

#include "peer_stdlib.h"

t_block	*find_block(void *ptr, t_zone *zone) {
	t_block	*block = HEAP_SHIFT((void *)zone);

	for (; block != NULL; block = block->next) {
		if (ptr == BLOCK_SHIFT((void *)block)) {
			return (block);
		}
	}
	return (NULL);
}
