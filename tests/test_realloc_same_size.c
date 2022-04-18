//
// Created by Peer De bakker on 3/3/22.
//

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "malloc_internal.h"

void	test_same_pointer(const size_t size) {
	dprintf(2, "starting test_same_pointer for size %zu\n", size);
	void	*ptr = malloc(size);
	dprintf(2, "malloced %p for size %zu\n", ptr, size);
	void	*ptr2 = realloc(ptr, size);

	dprintf(2, "malloced %p for size %zu\n", ptr2, size);
	assert(ptr == ptr2);
	free(ptr);
}

int main() {
	printf("TINY=%zu, SMALL=%zu\n", TINY_BLOCK_SIZE, SMALL_BLOCK_SIZE);
	test_same_pointer(0);
	test_same_pointer(1);
	test_same_pointer(42);
	test_same_pointer(128);
	test_same_pointer(256);

	return (0);
}
