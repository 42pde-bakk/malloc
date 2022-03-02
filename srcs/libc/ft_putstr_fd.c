//
// Created by Peer De bakker on 3/2/22.
//

#include <unistd.h>
#include "libc.h"

void	ft_putstr_fd(const char *s, int fd) {
	int	ret;

	if (s)
		ret = write(fd, s, ft_strlen(s));
	(void)ret;
}
