//
// Created by Peer De bakker on 3/2/22.
//

#ifndef MALLOC_LIBC_H
#define MALLOC_LIBC_H

#include <stddef.h>
#include <stdbool.h>

size_t	ft_strlen(const char* str);

void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(const char* str, int fd);

void	ft_putnbr_base_fd(unsigned long long nb, int base, int fd, bool uppercase);

void	*ft_memset(void *b, int c, size_t len);
void	*ft_memcpy(void *dst, const void *src, size_t n);

#endif //MALLOC_LIBC_H
