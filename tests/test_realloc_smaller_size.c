//
// Created by Peer De bakker on 3/3/22.
//

#include "peer_stdlib.h"
//#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

void	test_same_pointer(const size_t size) {
	printf("size1=%zu, size2=%zu\n", size, size / 2);
	void	*ptr = malloc(size);
	void	*ptr2 = realloc(ptr, size / 2);

	printf("ptr=%p, ptr2=%p, is_same=%d\n", ptr, ptr2, (ptr == ptr2));
//	assert(ptr == ptr2);
	free(ptr2);
	printf("\n");
}

int main() {
//	printf("TINY=%zu, SMALL=%zu\n", TINY_BLOCK_SIZE, SMALL_BLOCK_SIZE);
	test_same_pointer(1); // real malloc returns a different pointer
	test_same_pointer(42); // real malloc returns the same pointer
	test_same_pointer(128); // real malloc returns the same pointer
	test_same_pointer(256); // real malloc returns the same pointer
	test_same_pointer(512); // real malloc returns the same pointer
	test_same_pointer(1024); // real malloc returns a different pointer
	test_same_pointer(2048); // real malloc returns the same pointer
	test_same_pointer(4096); // real malloc returns the same pointer
	printf("1 / 2 = %d\n", 1 / 2);
	return (0);
}
