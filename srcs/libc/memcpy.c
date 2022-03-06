//
// Created by Peer De bakker on 3/3/22.
//

#include <stddef.h>

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i = 0;
	char			*d = dst;
	const char		*s = src;

	if (dst == src)
		return (dst);
	while (i < n) {
		d[i] = s[i];
		++i;
	}
	return (dst);
}
