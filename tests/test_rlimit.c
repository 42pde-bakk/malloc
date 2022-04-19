//
// Created by Peer De bakker on 4/19/22.
//

#include <stdio.h>
#include <unistd.h>
#include <sys/resource.h>
#include <stdlib.h>
#include "malloc_internal.h"
#include "libc.h"

int main() {
	int exit_status = 0;
	const size_t BIG_SIZE = 30012;
	char *t;
	struct rlimit rpl;

	getrlimit(RLIMIT_DATA, &rpl);
//	dprintf(2, "Let's test our getrlimit behaviour\n");

	rpl.rlim_cur = BIG_SIZE;
	rpl.rlim_max = BIG_SIZE;

	if (setrlimit(RLIMIT_DATA, &rpl) < 0)
		dprintf(2, "setrlimit did not work\n");

	if (!(t = (char *)malloc(BIG_SIZE - 1000))) {
		ft_putstr_fd("malloc() should return ptr\n", STDERR_FILENO);
		exit_status = 1;
	}
	else
		ft_putstr_fd("nice job, malloc returned a pointer!\n", STDERR_FILENO);
	free(t);
	t = NULL;

	if ((t = (char *)malloc(BIG_SIZE))) {
		ft_putstr_fd("malloc() should return NULL\n", STDERR_FILENO);
		exit_status = 1;
	}
	else
		ft_putstr_fd("nice job, malloc did not in fact return a pointer!\n", STDERR_FILENO);
	free(t);
	return (exit_status);
}
