//
// Created by Peer De bakker on 2/14/22.
//

#include "peer_stdlib.h"
#include <stdio.h>

void* malloc(size_t size) {
    (void)size;
    printf("size = %lu\n", size);
    return (NULL);
}

int my_add(int a, int b) {
    return (a + b);
}

int my_subtract(int a, int b) {
    return (a - b);
}
