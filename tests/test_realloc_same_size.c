//
// Created by Peer De bakker on 3/3/22.
//

#include "peer_stdlib.h"
//#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

void	test_same_pointer(const size_t size) {
	void	*ptr = malloc(size);
	void	*ptr2 = realloc(ptr, size);

	printf("ptr=%p, ptr2=%p\n", ptr, ptr2);
	assert(ptr == ptr2);
	free(ptr);
}

int main() {
	test_same_pointer(0);
	test_same_pointer(1);
	test_same_pointer(42);
	test_same_pointer(128);
	test_same_pointer(256);

	return (0);
}
