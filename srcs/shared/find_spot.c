//
// Created by Peer De bakker on 3/1/22.
//

#include "peer_stdlib.h"
#include <stdio.h>
#include <assert.h>

t_block	*zone_loop_through_blocks(t_zone* zone, size_t size) {
	t_block	*block = (t_block *)ZONE_SHIFT((void *)zone); // shifting zone forwards and casting it to a block ptr
	void	*zone_end = (void *)zone + TINY_HEAP_ALLOCATION_SIZE;

	while (block) {
		if (check_block(block, size, zone))
			return (init_block(block, size, zone));
		if (block->next == NULL) {
			void	*next_block_start = BLOCK_SHIFT((void*)block) + block->data_size;
			if (zone_end - next_block_start > (long)(sizeof(t_block) + size)) { // can append a new block to this zone
				block->next = next_block_start;
			}
		}
		block = block->next;
	}
	// Now, we couldn't find a big enough zone to store this allocation in, on to the next zone
	return (NULL);
}

// TODO: remove
void	print_ll_forwards(t_zone* zone) {
	t_zone *tmp = zone;
	while (tmp->prev)
		tmp = tmp->prev;
	while (tmp) {
		printf("%p (%zu)\t", (void*)tmp, tmp->total_size);
		tmp = tmp->next;
	}
}

void	print_ll_backwards(t_zone* zone) {
	t_zone *tmp = zone;
	while (tmp->next)
		tmp = tmp->next;
	while (tmp) {
		printf("%p (%zu)\t", (void*)tmp, tmp->total_size);
		tmp = tmp->prev;
	}
}

t_block	*loop_through_zones(t_zone* zone, size_t size, size_t allocation_size) {
	void	*res;

	while ((res = zone_loop_through_blocks(zone, size)) == NULL) {
		if (zone->next == NULL) {
			zone->next = allocate_new_zone(allocation_size);
			if (zone->next == MAP_FAILED)
				return (NULL);
			zone->next->prev = zone;
		}
		zone = zone->next;
	}
	return (res);
}

t_block* find_spot(size_t size) {
	assert(assert_zones() == 0); // TODO: remove assert()

	if (size <= SMALL_BLOCK_SIZE) {
		if (size <= TINY_BLOCK_SIZE) {
			return (loop_through_zones(g_coll.tiny, size, TINY_HEAP_ALLOCATION_SIZE));
		}
		else {
			return (loop_through_zones(g_coll.small, size, SMALL_HEAP_ALLOCATION_SIZE));
		}
	}
	dprintf(2, "LARGE not implemented yet\n");
	return (NULL);
}
