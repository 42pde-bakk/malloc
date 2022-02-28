//
// Created by Peer De bakker on 2/14/22.
//

#ifndef MALLOC_PEER_STDLIB_H
#define MALLOC_PEER_STDLIB_H

# include <stddef.h> // size_t

# include <sys/mman.h> // mmap & munmap (2)
# include <unistd.h> // getpagesize (2/3)
# include <sys/resource.h> // getrlimit (2)

# include <sys/errno.h> // TODO: REMOVE
extern int errno;

typedef struct s_alloc {
  void*     ptr;
  size_t    size;
  int       freed;

  struct s_alloc* prev;
  struct s_alloc* next;
} Alloc;

typedef struct s_zone {
    void*       start;
    size_t      size;
    size_t      allocated_size;
    size_t      allocations_amount;

    struct s_zone* prev;
    struct s_zone* next;
} Zone;

void free(void *ptr);
void *malloc(size_t size);
void *realloc(void *ptr, size_t size);

#endif //MALLOC_PEER_STDLIB_H
