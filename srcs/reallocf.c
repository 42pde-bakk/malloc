//
// Created by Peer De bakker on 3/3/22.
//

#include <stddef.h>
#include "malloc_internal.h"

void *reallocf(void *ptr, size_t size) {
	void *res;

	pthread_mutex_lock(&g_mutex);
	res = realloc_internal(ptr, size);
	if (res == NULL) {
		free_internal(ptr);
	}
	pthread_mutex_unlock(&g_mutex);
	return (res);
}
