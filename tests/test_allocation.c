//
// Created by Peer De bakker on 3/2/22.
//

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

void	show_alloc_mem();

void check_allocations(const size_t SIZE) {
	int i = 0;
	const size_t alloc_amount = 10;
	char*	allocs[alloc_amount];

	while (i < alloc_amount) {
		allocs[i] = (char*)malloc(SIZE);
		strcpy(allocs[i], "malloc\0");
		printf("allocs[%d] = '%s', %p\n", i, allocs[i], (void *)allocs[i]);
		i++;
	}
}


int main() {
	printf("\n");
	printf("Let's check tiny allocations:\n");
	check_allocations(0);
	check_allocations(25);
	check_allocations(1);
	printf("Let's check small allocations:\n");
	check_allocations(42);
	check_allocations(256);
	check_allocations(1025);
	printf("Let's check large allocations:\n");
	check_allocations(2500);

	show_alloc_mem();
	return (0);
}
