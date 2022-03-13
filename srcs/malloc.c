//
// Created by Peer De bakker on 2/14/22.
//

#include "peer_stdlib.h"
#include <stdio.h>

void* malloc(size_t size) {
	void	*res;

	pthread_mutex_lock(&g_mutex);
	res = find_spot(size);
	pthread_mutex_unlock(&g_mutex);
	return (res);
}
