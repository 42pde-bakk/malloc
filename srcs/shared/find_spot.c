//
// Created by Peer De bakker on 3/1/22.
//

#include "peer_stdlib.h"

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

static size_t	get_needed_size(const size_t size) {
	size_t	page_size = (size_t)getpagesize();
	size_t	min_size = size + sizeof(t_zone) + sizeof(t_block);
	size_t	alloc_size = page_size;

	while (alloc_size < min_size)
		alloc_size += page_size;
	return (alloc_size);
}

t_block	*find_available_large_chunk(const size_t size) {
	t_zone	*tmp;
	t_block	*block;

	for (tmp = g_coll.large; tmp; tmp = tmp->next) {
		block = BLOCK_SHIFT((void *)tmp);
		if (block->status != ALLOCATED && size < block->data_size)
			return (block);
	}
	return (NULL);
}

t_block	*find_large_chunk(const size_t size) {
	size_t	needed_alloc_size;
	t_block	*res = find_available_large_chunk(size);
	if (res)
		return (res);
	needed_alloc_size = get_needed_size(size);
	t_zone	*new_zone = allocate_new_zone(needed_alloc_size);

	if (!new_zone)
		return (NULL);
	g_coll.large->prev = new_zone;
	new_zone->next = g_coll.large;
	g_coll.large = new_zone;
	return (ZONE_SHIFT(g_coll.large));
}

void	*find_spot(size_t size) {
	t_block	*res;
	if (assert_zones())
		return (NULL);

	if (size <= TINY_BLOCK_SIZE)
		res = loop_through_zones(g_coll.tiny, size, TINY_HEAP_ALLOCATION_SIZE);
	else if (size <= SMALL_BLOCK_SIZE)
		res = loop_through_zones(g_coll.small, size, SMALL_HEAP_ALLOCATION_SIZE);
	else {
		res = find_large_chunk(size);
	}
	return (BLOCK_SHIFT((void *)res));
}
