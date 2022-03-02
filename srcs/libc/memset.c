//
// Created by Peer De bakker on 3/2/22.
//

#include <stddef.h>

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i = 0;
	unsigned char	*ptr = (unsigned char *)b;

	while (i < len) {
		ptr[i] = c;
		++i;
	}
	return (b);
}
