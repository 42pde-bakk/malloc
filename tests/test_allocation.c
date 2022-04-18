//
// Created by Peer De bakker on 3/2/22.
//

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

void check_allocations(const size_t SIZE) {
	int i = 0;
	const size_t alloc_amount = 10000;
	char*	allocs[alloc_amount];

	while (i < alloc_amount) {
		allocs[i] = (char*)malloc(SIZE);
		strcpy(allocs[i], "malloc\0");
		printf("allocs[%d] = '%s', %p\n", i, allocs[i], (void *)allocs[i]);
		i++;
	}
}


int main() {
	printf("lets check tiny allocations:\n");
	check_allocations(25);
	printf("lets check small allocations:\n");
	check_allocations(88);
	return (0);
}
