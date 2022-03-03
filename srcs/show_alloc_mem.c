//
// Created by Peer De bakker on 3/2/22.
//

#include <stdio.h>
#include "peer_stdlib.h"
#include "libc.h"

void	print_block_content(void *ptr_start, void *ptr_end, size_t amount_bytes) {
	int fd = STDOUT_FILENO;
	ft_putnbr_base_fd((unsigned long long)ptr_start, 16, fd);
	ft_putstr_fd(" - ", fd);
	ft_putnbr_base_fd((unsigned long long)ptr_end, 16, fd);
	ft_putstr_fd(" : ", fd);
	ft_putnbr_base_fd((unsigned long long)amount_bytes, 10, fd);
	ft_putstr_fd(" bytes\n", fd);
}

// Returns the total
static size_t	show_blocks(const t_block* block) {
	size_t	total = 0;
	for (; block != NULL; block = block->next) {
		void* end = (void*)g_coll.tiny + TINY_HEAP_ALLOCATION_SIZE;
		printf("zone: [%p - %p], ", (void*)g_coll.tiny, (void*)g_coll.tiny + TINY_HEAP_ALLOCATION_SIZE);
		printf("block @ %p, diff between end of zone and block is %zu\n", (void*)block, end - (void*)block);
		void	*ptr_start = BLOCK_SHIFT(block);
		void	*ptr_end = ptr_start + block->data_size;
		print_block_content(ptr_start, ptr_end, block->data_size);
//		printf("%p - %p : %zu bytes\n", ptr_start, ptr_end, block->data_size);
		total += block->data_size;
	}
	return (total);
}

static void	print_zone_header(const char* str, void *zone_addr) {
	int fd = STDOUT_FILENO;
	ft_putstr_fd(str, fd);
	ft_putstr_fd(" : ", fd);
	ft_putnbr_base_fd((unsigned long long) zone_addr, 16, fd);
}

static size_t	show_zones(const t_zone* zone, const char* str) {
	size_t	total_size = 0;
	for (const t_zone* tmp = zone; tmp; tmp = tmp->next) {
		print_zone_header(str, (void *)zone);
		total_size += show_blocks(ZONE_SHIFT(zone));
	}
	return (total_size);
}

void	show_alloc_mem() {
	size_t	total = 0;

	total += show_zones(g_coll.tiny, "TINY");
	total += show_zones(g_coll.small, "SMALL");
	total += show_zones(g_coll.large, "LARGE");

	printf("Total : %zu bytes\n", total);
}
