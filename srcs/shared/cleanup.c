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

void	cleanup() {
	unmap_all_zones(g_coll.tiny);
	unmap_all_zones(g_coll.small);
	unmap_all_zones(g_coll.large);
}
