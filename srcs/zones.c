//
// Created by Peer De bakker on 3/1/22.
//

#include "peer_stdlib.h"

t_zone	*find_zone(void *ptr) {
	// Also do it for small and large
	for (t_zone* tmp = tiny; tiny != NULL; tiny = tiny->next) {
		if ((void *)tmp < ptr && ptr < (void *)tmp + TINY_HEAP_ALLOCATION_SIZE)
			return (tmp);
	}
	return (NULL);
}
