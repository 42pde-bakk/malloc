//
// Created by Peer De bakker on 3/3/22.
//

#include "peer_stdlib.h"
#include <stdio.h>
#include <assert.h>

void	test_munmap_zone() {
	size_t max_nb = 150;
	void	*ptrs_tiny[max_nb];
	void	*ptrs_small[max_nb];

	for (int i = 0; i < max_nb; ++i) {
		ptrs_tiny[i] = malloc(TINY_BLOCK_SIZE);
		printf("ptrs_tiny[%d] = %p\n", i, ptrs_tiny[i]);
		ptrs_small[i] = malloc(SMALL_BLOCK_SIZE);
	}
	assert(g_coll.tiny->next != NULL);
	show_alloc_mem();

	for (int i = max_nb - 1; i >= 0; --i) {
		printf("ptrs_tiny[%d] = %p\n", i, ptrs_tiny[i]);
		free(ptrs_tiny[i]);
		free(ptrs_small[i]);
	}
	assert(g_coll.tiny->next == NULL);
}

int main() {
	test_munmap_zone();
	printf("TINY_BLOCK_SIZE = %zu, SMALL_BLOCK_SIZE = %zu\n", TINY_BLOCK_SIZE, SMALL_BLOCK_SIZE);
}
