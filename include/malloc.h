//
// Created by Peer De bakker on 2/14/22.
//

#ifndef MALLOC_MALLOC_H
#define MALLOC_MALLOC_H
#include <stddef.h>

void	free(void *ptr);
void	*calloc(size_t nmemb, size_t size);
void	*malloc(size_t size);
void	*realloc(void *ptr, size_t size);
void	*reallocf(void *ptr, size_t size);
void	show_alloc_mem();


#endif //MALLOC_MALLOC_H
