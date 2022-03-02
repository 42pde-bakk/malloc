//
// Created by Peer De bakker on 3/1/22.
//

#include "peer_stdlib.h"
#include <assert.h> // TODO: Remove
#include <stdio.h>

void	*allocate_new_zone(const size_t allocation_size) {
	assert(allocation_size % getpagesize() == 0);

	void	*zone = mmap(NULL, allocation_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
	return (zone);
}

t_zone	*find_zone(void *ptr) {
	// Also do it for small and large
	t_zone	*zone_sections[] = {
			g_coll.tiny, g_coll.small, g_coll.large
	};

	for (size_t i = 0; i < 3; ++i) {
		for (t_zone* tmp = zone_sections[i]; tmp != NULL; tmp = tmp->next) {
			if ((void *) tmp < ptr && ptr < (void *) tmp + TINY_HEAP_ALLOCATION_SIZE) {
				printf("found ptr %p in zone_section %zu\n", ptr, i);
				return (tmp);
			}
		}
	}
	return (NULL);
}
