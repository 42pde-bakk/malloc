//
// Created by Peer De bakker on 3/3/22.
//

#include "peer_stdlib.h"

static void	unmap_all_zones(t_zone* zone) {
	t_zone	*tmp;
	while (zone) {
		tmp = zone;
		zone = zone->next;
		munmap((void *)tmp, tmp->total_size);
	}
}

void	cleanup() {
	unmap_all_zones(g_coll.tiny);
	unmap_all_zones(g_coll.small);
	unmap_all_zones(g_coll.large);
}
