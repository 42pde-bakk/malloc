//
// Created by Peer De bakker on 2/14/22.
//

#include "peer_stdlib.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>


void	test_invalid_free() {
	printf("main @ %p\n", test_invalid_free);
	free(test_invalid_free);
}

void	test_double_free() {
	void	*ptr = malloc(88);
	printf("ptr = %p\n", ptr);
	free(ptr);
	printf("after first free\n");
	free(ptr);
	printf("after second free\n");
}

void	alloc_test() {
    while (true) {
    	void* ptr = malloc(23);
    	printf("PTR = %p\n", ptr);
    	if (ptr == NULL)
    		break;
    }
    void* ptr2 = malloc(41);
    printf("ptr2=%p\n", ptr2);
}

int main() {
	printf("t_block is size %zu, t_zone is size %zu\n", sizeof(t_block), sizeof(t_zone));
	test_double_free();
	test_invalid_free();
	alloc_test();
}
