//
// Created by Peer De bakker on 3/26/22.
//

#include "peer_stdlib.h"

t_block *block_init(t_block *b, const size_t size) {
	b->data_size = size;
	b->free = 0;
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

	while (tmp->next) {
		tmp = tmp->next;
	}
	tmp->next = new_block;
}
