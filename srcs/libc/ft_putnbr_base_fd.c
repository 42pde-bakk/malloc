//
// Created by Peer De bakker on 3/2/22.
//

#include "libc.h"

void	ft_putnbr_base_fd(unsigned long long nb, int base, int fd) {
	char tab[] = "0123456789abcdefghijklmnopqrstuvwxyz";

	if (nb >= (unsigned long long)base) {
		ft_putnbr_base_fd(nb / base, base, fd);
		ft_putnbr_base_fd(nb % base, base, fd);
	} else {
		ft_putchar_fd(tab[nb], fd);
	}
}
