//
// Created by Peer De bakker on 3/2/22.
//

#include <stdlib.h>
#include <stdio.h>

int main() {
	printf("main @ %p\n", main);
	free(main);
	printf("after trying to free a non-allocated pointer, our program didnt crash\n");
	return (0);
}
