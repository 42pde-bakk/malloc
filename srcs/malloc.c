//
// Created by Peer De bakker on 2/14/22.
//

#include "peer_stdlib.h"
#include <stdio.h>


void* malloc(size_t size) {
    t_block	*block = find_spot(size);
    if (!block)
		return (NULL);
    void	*ptr = BLOCK_SHIFT((void *)block);
//    printf("malloc: block=%p, ptr = %p\n", (void*)block, ptr);
    return (ptr);
}
