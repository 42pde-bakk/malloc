//
// Created by Peer De bakker on 3/3/22.
//

#include "peer_stdlib.h"
#include <stdio.h>

static void	unmap_all_zones(t_heap* zone) {
	t_heap	*tmp;
	while (zone) {
		tmp = zone;
		zone = zone->next;
		int ret = munmap((void *)tmp, tmp->total_size);
		if (ret) {
			// TODO: remove
			perror("munmap");
		}
	}
}

static void	unmap_large() {
	t_block*	prev;
	t_block*	tmp = g_malloc_zones.large;
	while (tmp) {
		prev = tmp;
		tmp = tmp->next;
		if (munmap((void *)prev, prev->data_size)) {
			// TODO: Remove
			perror("Munmap large");
		}
	}
}

void	cleanup() {
	unmap_all_zones(g_malloc_zones.tiny);
	g_malloc_zones.tiny = NULL;
	unmap_all_zones(g_malloc_zones.small);
	g_malloc_zones.small = NULL;
	unmap_large();
	g_malloc_zones.large = NULL;
}
