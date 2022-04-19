//
// Created by Peer De bakker on 4/18/22.
//
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include "malloc_internal.h"

void	check(void* ptr) {
	printf("is ptr %p 16byte aligned?: %d\n", ptr, ((uintptr_t)ptr & 0xFu) == 0);
}

size_t	align_16bytes(const size_t size) {
	return (size + 15u) & ~0xFu;
}

bool	isTiny(const size_t size) {
	return (size <= TINY_BLOCK_SIZE);
}

bool	isSmall(const size_t size) {
	return (TINY_BLOCK_SIZE < size && size <= SMALL_BLOCK_SIZE);
}

bool	isLarge(const size_t size) {
	return (size > SMALL_BLOCK_SIZE);
}

bool	isSameCategory(const size_t a, const size_t b) {
	return ((isTiny(a) && isTiny(b)) || (isSmall(a) && isSmall(b)) || (isLarge(a) && isLarge(b)));
}

rlim_t get_rlimit_data() {
	struct rlimit rpl;

	if (getrlimit(RLIMIT_DATA, &rpl) < 0)
		return (-1);
	return (rpl.rlim_max);
}
