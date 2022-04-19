//
// Created by Peer De bakker on 3/3/22.
//

#include "malloc_internal.h"
#include "libc.h"

void *calloc(size_t nmemb, size_t size) {
	void	*ptr;

	pthread_mutex_lock(&g_mutex);
	ptr = malloc_internal(nmemb * size);
	if (ptr)
		ft_memset(ptr, 0, nmemb * size);
	pthread_mutex_unlock(&g_mutex);
	return (ptr);
}
