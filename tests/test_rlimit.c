//
// Created by Peer De bakker on 4/19/22.
//

#include <stdio.h>
#include <unistd.h>
#include <sys/resource.h>
#include <stdlib.h>
#include "malloc_internal.h"

void run_test_rlimit()
{
	char *t;
	struct rlimit rpl;

	rpl.rlim_cur = TINY_HEAP_ALLOCATION_SIZE;
	rpl.rlim_max = TINY_HEAP_ALLOCATION_SIZE;

	if (setrlimit(RLIMIT_DATA, &rpl) < 0)
		printf("setrlimit did not work\n");

	if (!(t = (char *)malloc(TINY_HEAP_ALLOCATION_SIZE - sizeof(t_block) - sizeof(t_heap))))
		printf("malloc() should return ptr\n");
	free(t);

	if ((t = (char *)malloc(TINY_HEAP_ALLOCATION_SIZE)))
		printf("malloc() should return NULL\n");
	free(t);
}
