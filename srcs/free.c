//
// Created by Peer De bakker on 2/14/22.
//

#include "peer_stdlib.h"
#include <stdio.h>

static void	error_free(void *ptr) {
	dprintf(2, "malloc *** error for object %p: pointer being freed was not allocated\n", ptr);
	dprintf(2, "malloc: *** set a breakpoint in malloc_error_break to debug\n");
	// cleanup
}

void    free(void* ptr) {
	t_zone	*zone;
	t_block	*block;

	if (!ptr)
		return ;

	zone = find_zone(ptr);
	if (!zone)
		return (error_free(ptr));
	block = find_block(ptr, zone);
	if (!block || block->status == FREED)
		return (error_free(ptr));
	block->status = FREED;
	// try to combine freed blocks if possible (or is that bonus)
	--zone->block_count;
}
