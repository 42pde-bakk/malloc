//
// Created by Peer De bakker on 3/3/22.
//

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "malloc_internal.h"

void	test_munmap_zone() {
	size_t	max_nb = 150;
	void	*ptrs_tiny[max_nb];
	void	*ptrs_small[max_nb];

	for (size_t i = 0; i < max_nb; ++i) {
		ptrs_tiny[i] = malloc(245);
		printf("malloc: ptrs_tiny[%zu] = %p, %llu\n", i, ptrs_tiny[i], (unsigned long long)ptrs_tiny[i]);
		ptrs_small[i] = malloc(1057);
		printf("malloc: ptrs_small[%zu] = %p\n", i, ptrs_small[i]);
	}
	assert(g_malloc_zones.tiny->next != NULL);
	show_alloc_mem();

	for (size_t i = 0; i < max_nb; i++) {
		printf("free: ptrs_tiny[%zu] = %p\n", i, ptrs_tiny[i]);
		free(ptrs_tiny[i]);
		printf("free: ptrs_small[%zu] = %p\n", i, ptrs_small[i]);
		free(ptrs_small[i]);
	}
	assert(g_malloc_zones.tiny->next == NULL);
}

int main() {
	test_munmap_zone();
	printf("TINY_BLOCK_SIZE = %d, SMALL_BLOCK_SIZE = %d\n", 25, 80);
}
