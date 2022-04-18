//
// Created by Peer De bakker on 3/3/22.
//

#include "malloc_internal.h"
#include "libc.h"

void *calloc(size_t nmemb, size_t size) {
	void	*ptr;

	//	pthread_mutex_lock(&g_mutex);
	dprintf(2, "calling calloc(%zu, %zu)\n", nmemb, size);
	ptr = malloc_internal(nmemb * size);
	if (ptr)
		ft_memset(ptr, 0, nmemb * size);
	dprintf(2, "calloc returns %p\n", ptr);
	//	pthread_mutex_unlock(&g_mutex);
	return (ptr);
}
