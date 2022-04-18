//
// Created by Peer De bakker on 3/2/22.
//

#include "malloc_internal.h"

t_malloc_zones g_malloc_zones = {
		.tiny = NULL,
		.small = NULL,
		.large = NULL
};
pthread_mutex_t	g_mutex = PTHREAD_MUTEX_INITIALIZER;
