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
# include <pthread.h> // mutex

# include <sys/errno.h> // TODO: REMOVE
extern int errno;

#include <stdio.h>

typedef struct s_block {
  size_t    data_size;
  int		free;

  struct s_block* next;
} t_block;

typedef struct s_heap {
	size_t  total_size;
	size_t  block_count;

	struct s_heap* prev;
	struct s_heap* next;
} t_heap;

typedef struct s_malloc_zones {
	t_heap	*tiny,
			*small;
	t_block	*large;
} t_malloc_zones;

extern t_malloc_zones g_malloc_zones;
extern pthread_mutex_t g_mutex;


# define ZONE_SHIFT(start) ((void *)start + sizeof(t_heap))
# define BLOCK_SHIFT(start) ((void *)start + sizeof(t_block))

# define TINY_HEAP_ALLOCATION_SIZE (size_t)(1 * getpagesize()) // 4
# define TINY_BLOCK_SIZE (size_t)(TINY_HEAP_ALLOCATION_SIZE / 128)
# define SMALL_HEAP_ALLOCATION_SIZE (size_t)(4 * getpagesize()) // 16
# define SMALL_BLOCK_SIZE (size_t)(SMALL_HEAP_ALLOCATION_SIZE / 128)

void free(void *ptr);
void *malloc(size_t size);
void *realloc(void *ptr, size_t size);

// shared.c

// zones.c
t_heap *allocateHeap(size_t alloc_size);
void	heap_push_back(t_heap** heap, t_heap* new_heap);
void	extend_heap(t_heap* heap, size_t alloc_size);

// t_block.c
t_block *block_init(t_block *b, size_t size);
void	block_push_back(t_block ** blocks, t_block* new_block);

// defragment.c
void	declutter_freed_areas(t_block *block);

// show_alloc_mem.c
void	show_alloc_mem();

//cleanup.c
void	cleanup();

#endif //MALLOC_PEER_STDLIB_H
