//
// Created by Peer De bakker on 3/2/22.
//

#include <stddef.h>

size_t	ft_strlen(const char *s)
{
	size_t	i = 0;
	while (s[i])
		++i;
	return (i);
}
