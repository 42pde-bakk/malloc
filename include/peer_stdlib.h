//
// Created by Peer De bakker on 2/14/22.
//

#ifndef MALLOC_PEER_STDLIB_H
#define MALLOC_PEER_STDLIB_H

# include <stddef.h> // size_t
# include <stdbool.h> // bool

# include <sys/mman.h> // mmap & munmap (2)
# include <unistd.h> // getpagesize (2/3)
# include <sys/resource.h> // getrlimit (2)

# include <sys/errno.h> // TODO: REMOVE
extern int errno;

typedef enum s_state {
	AVAILABLE,
	ALLOCATED,
	FREED
} t_state;

typedef struct s_block {
  size_t    data_size;
  int       status:3; // maybe its better to change this to available

  struct s_block* prev;
  struct s_block* next;
} t_block;

typedef struct s_zone {
	size_t  total_size;
	size_t  free_size;
	size_t  block_count;

	struct s_zone* prev;
	struct s_zone* next;
} t_zone;

extern t_zone* tiny;


# define HEAP_SHIFT(start) ((void *)start + sizeof(t_zone))
# define BLOCK_SHIFT(start) ((void *)start + sizeof(t_block))

# define TINY_HEAP_ALLOCATION_SIZE 4 * getpagesize()
# define TINY_BLOCK_SIZE (TINY_HEAP_ALLOCATION_SIZE / 128)
# define SMALL_HEAP_ALLOCATION_SIZE (16 * getpagesize())
# define SMALL_BLOCK_SIZE (SMALL_HEAP_ALLOCATION_SIZE / 128)

void free(void *ptr);
void *malloc(size_t size);
void *realloc(void *ptr, size_t size);

// shared.c
void* find_spot(size_t size);

// zones.c
t_zone	*find_zone(void *ptr);

// blocks.c
t_block	*find_block(void *ptr, t_zone *zone);

#endif //MALLOC_PEER_STDLIB_H
