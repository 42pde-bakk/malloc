//
// Created by Peer De bakker on 3/1/22.
//

#include "peer_stdlib.h"
#include <stdio.h>
#include <assert.h>


size_t  get_available_space(const t_block* block, const void* zone_end) {
	void* block_data = BLOCK_SHIFT((void *)block);

	if (block->next)
		return ((void *)block->next - block_data);
	return (zone_end - block_data);
}

int check_block(const t_block* block, const size_t size, t_zone* zone) {
	if (block->status == ALLOCATED)
		return (0);

	return (size <= get_available_space(block, (void *)zone + TINY_HEAP_ALLOCATION_SIZE));
}

void	*init_block(t_block* block, const size_t size) {
	block->status = ALLOCATED;
	block->data_size = size;
	return (BLOCK_SHIFT((void *)block));
}

void	*loop_zone(t_zone* zone, size_t size) {
	t_block	*block = (t_block *)HEAP_SHIFT((void *)zone); // shifting zone forwards and casting it to a block ptr
	void	*zone_end = (void *)zone + TINY_HEAP_ALLOCATION_SIZE;

	while (block) {
		printf("while %p\n", (void*)block);
		if (check_block(block, size, zone)) {
			printf("check_block returned 1, block is %p\n", (void*)block);
			++zone->block_count;
			return (init_block(block, size));
		}
		printf("after chcek_nl\n");
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

void	*loop_through_zones(t_zone* zone, size_t size, size_t allocation_size) {
	void	*res;

	while ((res = loop_zone(zone, size)) == NULL) {
		if (zone->next == NULL) {
			zone->next = allocate_new_zone(allocation_size);
			if (zone->next == MAP_FAILED)
				return (NULL);
		}
		zone = zone->next;
	}
	return (res);
}

int	check_allocation(t_zone** zone, const size_t size) {
	if (*zone)
		return (0);
	*zone = allocate_new_zone(size);
	return (*zone == MAP_FAILED);
}

static int	assert_zones() {
	// returns 1 if any of the allocations fail
	return (
		(g_coll.tiny == NULL && check_allocation(&g_coll.tiny, TINY_HEAP_ALLOCATION_SIZE)) ||
		(g_coll.small == NULL && check_allocation(&g_coll.small, SMALL_HEAP_ALLOCATION_SIZE)) ||
		(g_coll.large == NULL && check_allocation(&g_coll.large, getpagesize()))
	);
}

void* find_spot(size_t size) {
	assert(assert_zones() == 0);
	printf("assertion = %d\n", assert_zones());

	if (size < SMALL_BLOCK_SIZE) {
		if (size <= TINY_BLOCK_SIZE) {
			return (loop_through_zones(g_coll.tiny, size, TINY_HEAP_ALLOCATION_SIZE));
		}
		else {
			return (loop_through_zones(g_coll.small, size, SMALL_HEAP_ALLOCATION_SIZE));
		}
	}
	printf("LARGE not implemented yet\n");
	return (NULL);
}
