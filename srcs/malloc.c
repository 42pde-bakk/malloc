//
// Created by Peer De bakker on 2/14/22.
//

#include "peer_stdlib.h"
#include <stdio.h>

void* malloc(size_t size) {
    int pagesize = getpagesize();

    void* ptr = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_ANON, -1, 0);
    /* addr = NULL
     * len = size
     * prot = PROT_READ | PROT_WRITE
     * flags = MAP_ANON
     * fd = -1
     * offset = 0
    */
    if (ptr == MAP_FAILED)
        return (NULL);
    return (ptr);
}
