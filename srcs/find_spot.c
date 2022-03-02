//
// Created by Peer De bakker on 3/1/22.
//

#include "peer_stdlib.h"
#include <stdio.h>


int init_zones() {
	g_coll.tiny = mmap(NULL, TINY_HEAP_ALLOCATION_SIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
	g_coll.small = mmap(NULL, SMALL_HEAP_ALLOCATION_SIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
	g_coll.large = NULL;
	printf("g_coll.tiny = %p", g_coll.tiny);
	printf("g_coll.small = %p", g_coll.small);
	printf("g_coll.large = %p", g_coll.large);
	if (g_coll.tiny == MAP_FAILED) {
		perror("mmap tiny: ");
		return (1);
	}
	return (0);
}

size_t  get_available_space(const t_block* block, const void* zone_end) {
	void* block_data = BLOCK_SHIFT((void *)block);

	if (block->next)
		return ((void *)block->next - block_data);
	return (zone_end - block_data);
}

int check_block(const t_block* block, const size_t size, t_zone* zone) {
	if (block->status == ALLOCATED) {
		return (0);
	}
	return (size <= get_available_space(block, (void *)zone + TINY_HEAP_ALLOCATION_SIZE));
}

void	*init_block(t_block* block, const size_t size) {
	block->status = ALLOCATED;
	block->data_size = size;
	return (BLOCK_SHIFT((void *)block));
}

void*	find_spot_in_zonesection(t_zone* zone, size_t size) {
	t_block	*block = (t_block *)HEAP_SHIFT((void *)zone); // shifting zone forwards and casting it to a block ptr

	while ((void *)block + sizeof(t_block) < (void *)zone + TINY_HEAP_ALLOCATION_SIZE) {
		if (check_block(block, size, zone)) {
			++zone->block_count;
			return (init_block(block, size)); // return the address of where the
		}
		if (!block->next) {
			t_block* next = BLOCK_SHIFT((void *)block);
			next->prev = block;
			block->next = next;
		}
		block = block->next;
	}
	return (NULL);
}

int	check_allocation(t_zone** zone, const size_t size) {
	if (*zone)
		return (0);
	*zone = allocate_new_zone(size);
	return (*zone == MAP_FAILED);
}

void* find_spot(size_t size) {
	if (size < SMALL_BLOCK_SIZE) {
		if (size <= TINY_BLOCK_SIZE) {
			if (check_allocation(&g_coll.tiny, TINY_HEAP_ALLOCATION_SIZE))
				return (NULL);
			return (find_spot_in_zonesection(g_coll.tiny, size));
		}
		else {
			if (check_allocation(&g_coll.small, SMALL_HEAP_ALLOCATION_SIZE))
				return (NULL);
			return (find_spot_in_zonesection(g_coll.small, size));
		}
	}
	printf("LARGE not implemented yet\n");
	return (NULL);
}
