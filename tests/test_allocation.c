//
// Created by Peer De bakker on 3/2/22.
//

#include "peer_stdlib.h"
#include <stdio.h>
#include <assert.h>

int main() {
	size_t	size1 = 23,
			size2 = 34;
	void	*ptr = malloc(size1);
	void	*ptr2 = malloc(size2);
	size_t diff = ptr2 - ptr;
	printf("diff = %zu\n", diff);
	assert(ptr2 - ptr == sizeof(t_block) + size1);

	return (0);
}
