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

#include <stdio.h>

typedef enum s_state {
	AVAILABLE = 0,
	ALLOCATED = 1,
	FREED = 2
} t_state;

typedef struct s_block {
  size_t    data_size;
  int       status:3; // maybe its better to change this to freed

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

typedef struct s_collection {
	t_zone	*tiny,
			*small,
			*large;
}	t_collection;

extern t_collection	g_coll;


# define ZONE_SHIFT(start) ((void *)start + sizeof(t_zone))
# define BLOCK_SHIFT(start) ((void *)start + sizeof(t_block))

# define TINY_HEAP_ALLOCATION_SIZE (size_t)(4 * getpagesize()) // 4
# define TINY_BLOCK_SIZE (size_t)(TINY_HEAP_ALLOCATION_SIZE / 128)
# define SMALL_HEAP_ALLOCATION_SIZE (size_t)(16 * getpagesize()) // 16
# define SMALL_BLOCK_SIZE (size_t)(SMALL_HEAP_ALLOCATION_SIZE / 128)

typedef enum s_category {
	ZERO,
	TINY,
	SMALL,
	LARGE
}	t_category;

void free(void *ptr);
void *malloc(size_t size);
void *realloc(void *ptr, size_t size);

// shared.c
void *find_spot(size_t size);

// zones.c
t_zone * allocate_new_zone(size_t allocation_size);
t_zone	*get_zonesection(size_t allocation_size);
t_zone	*check_smaller_zones(void *ptr);
t_zone	*check_large_zone_ll(void *ptr);
int		assert_zones();

// blocks.c
int		check_block(const t_block* block, size_t size, t_zone* zone);
t_block	*init_block(t_block* block, size_t size, t_zone* zone);
void	release_block(t_block* block, t_zone* zone);
t_block	*find_block(void *ptr, t_zone *zone);

// defragment.c
void	declutter_freed_areas(t_block *block);

// show_alloc_mem.c
void	show_alloc_mem();

//cleanup.c
void	cleanup();

#endif //MALLOC_PEER_STDLIB_H
