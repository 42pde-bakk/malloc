//
// Created by Peer De bakker on 2/14/22.
//

#ifndef MALLOC_PEER_STDLIB_H
#define MALLOC_PEER_STDLIB_H

# include <stddef.h> // size_t

# include <sys/mman.h> // mmap & munmap (2)
# include <unistd.h> // getpagesize (2/3)
# include <sys/resource.h> // getrlimit (2)

void free(void *ptr);
void *malloc(size_t size);
void *realloc(void *ptr, size_t size);

#endif //MALLOC_PEER_STDLIB_H
