//
// Created by Peer De bakker on 2/14/22.
//

#include "peer_stdlib.h"
#include <stdio.h>


void* malloc(size_t size) {
    void* ptr = find_spot(size);
    // TODO: check if there is space in the zone, otherwise allocate more
    printf("malloc: ptr = %p\n", ptr);
    return (ptr);
}
