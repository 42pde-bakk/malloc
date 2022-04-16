//
// Created by Peer De bakker on 2/14/22.
//

#include "peer_stdlib.h"
#include <stdio.h>
#include <assert.h>

static void	error_free(void *ptr) {
	dprintf(2, "malloc *** error for object %p: pointer being freed was not allocated\n", ptr);
	dprintf(2, "malloc: *** set a breakpoint in malloc_error_break to debug\n");
	pthread_mutex_unlock(&g_mutex);
}

void	release_zone(t_heap *zone) {
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


// not locking the mutex here
void	free_internal(void* ptr) {
	t_block	*result = NULL;
	if ((result = loop_heap(g_malloc_zones.tiny, ptr))) {
		result->free = 1;
		return ;
	}
	if ((result = loop_heap(g_malloc_zones.small, ptr))) {
		result->free = 1;
		return ;
	}
	if ((result = loop_blocks(g_malloc_zones.large, ptr, true))) {
		munmap(result, result->data_size);
		return ;
	}
	error_free(ptr);
}

void    free(void* ptr) {
	if (!ptr)
		return ;

	pthread_mutex_lock(&g_mutex);
	free_internal(ptr);
	pthread_mutex_unlock(&g_mutex);
}
