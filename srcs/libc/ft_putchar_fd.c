//
// Created by Peer De bakker on 3/2/22.
//

#include <unistd.h>

void	ft_putchar_fd(const char c, int fd) {
	int	ret = write(fd, &c, sizeof(char));
	(void)ret;
}
