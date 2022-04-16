//
// Created by Peer De bakker on 3/2/22.
//

#include "peer_stdlib.h"
#include <stdio.h>
#include <assert.h>

int main() {
	size_t	size1 = TINY_BLOCK_SIZE - 10,
			size2 = TINY_BLOCK_SIZE;
	void	*ptr = malloc(size1);
	void	*ptr2 = malloc(size2);
	size_t diff = ptr2 - ptr;
//	printf("diff = %zu, check if %zu\n", diff, sizeof(t_block) + size1);
//	assert(diff == sizeof(t_block) + size1);

	return (0);
}
