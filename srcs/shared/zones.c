//
// Created by Peer De bakker on 3/1/22.
//

#include "peer_stdlib.h"
#include <assert.h> // TODO: Remove

t_zone *allocate_new_zone(const size_t allocation_size) {
	assert(allocation_size % getpagesize() == 0);

	t_zone	*new_zone = mmap(NULL, allocation_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
	if (new_zone == MAP_FAILED)
		return (MAP_FAILED);
	new_zone->total_size = allocation_size;

	return (new_zone);
}

t_zone	*get_zonesection(const size_t allocation_size) {
	if (allocation_size <= TINY_BLOCK_SIZE)
		return g_coll.tiny;
	if (allocation_size <= SMALL_BLOCK_SIZE)
		return g_coll.small;
	return g_coll.large;
}

t_zone	*find_zone(void *ptr) {
	// Also do it for small and large
	t_zone	*zone_sections[] = {
			g_coll.tiny, g_coll.small, g_coll.large
	};

	for (size_t i = 0; i < 3; ++i) {
		for (t_zone* tmp = zone_sections[i]; tmp != NULL; tmp = tmp->next) {
			if ((void *) tmp < ptr && ptr < (void *) tmp + TINY_HEAP_ALLOCATION_SIZE) {
				return (tmp);
			}
		}
	}
	return (NULL);
}

static int	check_allocation(t_zone** zone, const size_t size) {
	if (*zone)
		return (0);
	*zone = allocate_new_zone(size);
	(*zone)->total_size = size;
	return (*zone == MAP_FAILED);
}

int	assert_zones() {
	// returns 1 if any of the allocations fail
	return (
			(g_coll.tiny == NULL && check_allocation(&g_coll.tiny, TINY_HEAP_ALLOCATION_SIZE)) ||
			(g_coll.small == NULL && check_allocation(&g_coll.small, SMALL_HEAP_ALLOCATION_SIZE)) ||
			(g_coll.large == NULL && check_allocation(&g_coll.large, 4 * getpagesize()))
	);
}
