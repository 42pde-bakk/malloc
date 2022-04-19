//
// Created by Peer De bakker on 4/18/22.
//

#ifndef MALLOC_MALLOC_INTERNAL_H
#define MALLOC_MALLOC_INTERNAL_H

# include <stddef.h> // size_t
# include <stdbool.h> // bool

# include <sys/mman.h> // mmap & munmap (2)
# include <unistd.h> // getpagesize (2/3)
# include <sys/resource.h> // getrlimit (2)
# include <pthread.h> // mutex

typedef struct s_block {
	size_t	data_size;
	int		dummy;
	int		free;

	struct s_block* prev;
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

extern t_malloc_zones	g_malloc_zones;
extern pthread_mutex_t	g_mutex;

#define PAGE_SIZE getpagesize()

# define HEAP_SHIFT(start) ((void *)(start) + sizeof(t_heap))
# define BLOCK_SHIFT(start) ((void *)(start) + sizeof(t_block))

# define TINY_HEAP_ALLOCATION_SIZE (size_t)(8 * PAGE_SIZE) // 4
# define TINY_BLOCK_SIZE (size_t)(TINY_HEAP_ALLOCATION_SIZE / 128)
# define SMALL_HEAP_ALLOCATION_SIZE (size_t)(64 * PAGE_SIZE) // 16
# define SMALL_BLOCK_SIZE (size_t)(SMALL_HEAP_ALLOCATION_SIZE / 128)

# ifndef DEBUG_FAULTY_POINTERS
#  define DEBUG_FAULTY_POINTERS 0
# endif

# ifndef BONUS
#  define BONUS 0
# endif

int		free_internal(void *ptr);
void	*malloc_internal(size_t size);
void	*realloc_internal(void *ptr, size_t size);


void	*free_block(t_heap* heap, t_block* block);

// find_ptr.c
typedef void*(*loop_func)(t_heap*,t_block*);
t_block	*loop_blocks(t_block* block, void* ptr);
void *loop_heap(t_heap *heap, void *ptr, loop_func func, t_block **block);
// shared.c

// zones.c
t_heap *allocateHeap(size_t alloc_size);
void	heap_push_back(t_heap** heap, t_heap* new_heap);
void	extend_heap(t_heap* heap, size_t alloc_size);
void	remove_heap_from_list(t_heap *heap);
void	release_heap(t_heap *heap);

// t_block.c
t_block *block_init(t_block *b, size_t size, int free);
void	block_push_back(t_block ** blocks, t_block* new_block);
void 	remove_block_from_list(t_block *block);

// defragment.c
void	declutter_freed_areas(t_block *block);

// show_alloc_mem.c
void	show_alloc_mem();

// utilities.c
size_t	align_16bytes(size_t size);
bool	isTiny(size_t size);
bool	isSmall(size_t size);
bool	isLarge(size_t size);
bool	isSameCategory(size_t a, size_t b);
rlim_t	get_rlimit_data();

#endif //MALLOC_MALLOC_INTERNAL_H
