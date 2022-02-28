//
// Created by Peer De bakker on 2/14/22.
//

#include "peer_stdlib.h"
#include <stdio.h>


static int    alloc_zone() {
    int pagesize = getpagesize();
    void* ptr = mmap(NULL, pagesize, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
    /* addr = NULL
     * len = size
     * prot = PROT_READ | PROT_WRITE
     * flags = MAP_ANON
     * fd = -1
     * offset = 0
    */
    printf("ptr = %p\n", ptr);
    if (ptr == MAP_FAILED) {
        perror("mmap: ");
        return (1);
    }
    // TODO: save ptr in global
    return (0);
}


void* malloc(size_t size) {
    // TODO: check if there is space in the zone, otherwise allocate more
    return (NULL);
}
