//
// Created by Peer De bakker on 2/14/22.
//

#include "peer_stdlib.h"
#include <stdio.h>
#include <assert.h>

static void	error_free(void *ptr) {
	dprintf(2, "malloc *** error for object %p: pointer being freed was not allocated\n", ptr);
	dprintf(2, "malloc: *** set a breakpoint in malloc_error_break to debug\n");
	// cleanup
}

void	release_zone(t_zone *zone) {
	if (zone->prev)
		zone->prev->next = zone->next;
	if (zone->next)
		zone->next->prev = zone->prev;
	int ret = munmap((void *)zone, zone->total_size);
	if (ret) {
		// TODO: remove
		perror("munmap");
		printf("tried to call munmap(%p, %zu)\n", (void*)zone, zone->total_size);
		assert(0);
	}
}

void    free(void* ptr) {
	t_zone	*zone;
	t_block	*block;

	if (!ptr)
		return ;

	zone = check_smaller_zones(ptr);
	if (!zone) {
		zone = check_large_zone_ll(ptr);
		if (zone)
			return (release_zone(zone));
		return (error_free(ptr));
	}
	block = find_block(ptr, zone);
	if (!block || block->status == FREED)
		return (error_free(ptr));

	release_block(block, zone);

	if (zone->block_count == 0 && (zone->prev || zone->next)) {
		// munmap the zone if it contains no blocks
		// but only if it isn't the only zone of it's size
		// Will this also work for my large ones?
		release_zone(zone);
	}
	// try to combine freed blocks if possible (or is that bonus)

}
