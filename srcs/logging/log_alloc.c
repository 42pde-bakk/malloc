//
// Created by Peer De bakker on 4/20/22.
//
#include "libc.h"
#include "malloc_internal.h"
#include <fcntl.h>
#define LOG_PATH "/tmp/malloc.log"

void log_malloc(const size_t size) {
	int fd;

	if ((fd = open(LOG_PATH, O_CREAT | O_WRONLY | O_APPEND, 0644))) {
		ft_putstr_fd("Allocated ", fd);
		ft_putnbr_base_fd(size, 10, fd, false);
		ft_putstr_fd(" bytes.\n", fd);
		close(fd);
	}
}

void log_free(const size_t size) {
	int fd;

	if ((fd = open(LOG_PATH, O_CREAT | O_WRONLY | O_APPEND, 0644))) {
		ft_putstr_fd("Freed ", fd);
		ft_putnbr_base_fd(size, 10, fd, false);
		ft_putstr_fd(" bytes.\n", fd);
		close(fd);
	}
}

void log_call(const char *str) {
	int fd;

	if ((fd = open(LOG_PATH, O_CREAT | O_WRONLY | O_APPEND, 0644))) {
		ft_putstr_fd("Called ", fd);
		ft_putstr_fd(str, fd);
		ft_putstr_fd(".\n", fd);
		close(fd);
	}
}

void log_heap_operation(const char *operation, void *ptr) {
	int fd;

	if ((fd = open(LOG_PATH, O_CREAT | O_WRONLY | O_APPEND, 0644))) {
		ft_putstr_fd(operation, fd);
		ft_putstr_fd(" heap ", fd);
		ft_putnbr_base_fd((unsigned long long int) ptr, 16, fd, false);
		ft_putstr_fd(".\n", fd);
		close(fd);
	}
}
