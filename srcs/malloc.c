//
// Created by Peer De bakker on 2/14/22.
//

#include "peer_stdlib.h"
#include <stdio.h>

void* malloc(size_t size) {
	return (find_spot(size));
}
