////
//// Created by Peer De bakker on 2/14/22.
////
//
//#include "peer_stdlib.h"
//#include "libc.h"
//#include <stdio.h>
//
//void *realloc(void *ptr, size_t size) {
//	if (!ptr)
//		return (malloc(size));
//
//	pthread_mutex_lock(&g_mutex);
//	t_heap* zone = check_smaller_zones(ptr);
//	if (!zone) {
//		// ptr is not in TINY or SMALL
//		zone = check_large_zone_ll(ptr);
//		pthread_mutex_unlock(&g_mutex);
//		if (zone)
//			return (ZONE_SHIFT(zone));
//		return (NULL);
//	}
//	t_block* block = find_block(ptr, zone);
//	if (!block) { // Invalidly aligned pionter
//		pthread_mutex_unlock(&g_mutex);
//		return (NULL);
//	}
//	if (size > block->data_size) {
//		t_block	*newblock = find_spot(size);
//		if (!newblock) { // It is not freed if realloc fails to obtain a large enough block of memory and returns NULL.
//			pthread_mutex_unlock(&g_mutex);
//			return (NULL);
//		}
//		void *new_ptr = ft_memcpy(BLOCK_SHIFT((void*)newblock), BLOCK_SHIFT((void*)block), block->data_size);
//		free(block); // if realloc() returns a pointer to a different location, the old location is freed.
//		pthread_mutex_unlock(&g_mutex);
//		return (new_ptr);
//	} else if (size < block->data_size) {
//		pthread_mutex_unlock(&g_mutex);
//		return (ptr); // do I need to create a new block with less range?
//	}
//	// If size == block->size, No operation
//	pthread_mutex_unlock(&g_mutex);
//    return (ptr);
//}
