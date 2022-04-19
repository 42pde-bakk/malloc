//
// Created by Peer De bakker on 4/19/22.
//

#include <stdio.h>
#include <unistd.h>
#include <sys/resource.h>
#include <stdlib.h>
#include "malloc_internal.h"

int main() {
	int exit_status = 0;
	const size_t BIG_SIZE = 30012;
	char *t;
	struct rlimit rpl;

	getrlimit(RLIMIT_DATA, &rpl);

	rpl.rlim_cur = BIG_SIZE;
	rpl.rlim_max = BIG_SIZE;

	if (setrlimit(RLIMIT_DATA, &rpl) < 0)
		dprintf(2, "setrlimit did not work\n");

	if (!(t = (char *)malloc(10000))) {
		dprintf(2, "malloc() should return ptr\n");
		exit_status = 1;
	}
	else
		dprintf(2, "nice job, malloc returned a pointer!\n");
	free(t);
	t = NULL;

	if ((t = (char *)malloc(BIG_SIZE))) {
		dprintf(2, "malloc() should return NULL\n");
		exit_status = 1;
	}
	else
		dprintf(2, "nice job, malloc did not in fact return a pointer!\n");
	free(t);
	return (exit_status);
}
