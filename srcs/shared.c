//
// Created by Peer De bakker on 3/1/22.
//

#include "peer_stdlib.h"
#include <stdio.h>

t_zone* tiny = NULL;

int init_zones() {
	tiny = mmap(NULL, TINY_HEAP_ALLOCATION_SIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
	printf("tiny = %p\n", (void*)tiny);
	if (tiny == MAP_FAILED) {
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

void* find_spot(size_t size) {
	t_zone* zone;

	if (tiny == NULL)
		init_zones();
	if (size <= (size_t)TINY_BLOCK_SIZE)
		zone = tiny;
	else
		return (NULL);
	// rn everything gon fit in tiny
	void* ptr = HEAP_SHIFT((void *)zone); // moves the zone pointer sizeof(t_zone) forwards
	t_block* block = (t_block *)ptr;

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
