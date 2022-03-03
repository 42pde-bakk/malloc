//
// Created by Peer De bakker on 3/2/22.
//

#include "peer_stdlib.h"
#include <stdio.h>

int main() {
	printf("main @ %p\n", main);
	free(main);
	return (0);
}
