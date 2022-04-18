//
// Created by Peer De bakker on 3/26/22.
//

#include <assert.h>
#include "malloc_internal.h"

t_block *block_init(t_block *b, size_t size, int free) {
	b->data_size = size;
	b->free = free;
	b->next = NULL;

	return (b);
}

t_block	*get_last_block(t_heap *zone) {
	t_block *b = (t_block *)ZONE_SHIFT(zone);

	while (b->next)
		b = b->next;
	return (b);
}

void	block_push_back(t_block **blocks, t_block* new_block) {
	t_block* tmp = *blocks;

	assert(blocks);

	if (tmp) {
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_block;
		new_block->prev = tmp;
	} else {
		*blocks = new_block;
	}
}

void remove_block_from_list(t_block *block) {
	if (block->prev)
		block->prev->next = block->next;
	if (block->next)
		block->next->prev = block->prev;
}
