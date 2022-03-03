//
// Created by Peer De bakker on 3/3/22.
//

#include "peer_stdlib.h"
#include "libc.h"

void	*calloc(size_t nmemb, size_t size) {
	void	*ptr;
	if (nmemb == 0 || size == 0)
		nmemb = size = 1;

	ptr = malloc(nmemb * size);
	if (ptr)
		ft_memset(ptr, 0, nmemb * size);
	return (ptr);
}
