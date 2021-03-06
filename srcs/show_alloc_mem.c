//
// Created by Peer De bakker on 3/2/22.
//

#include "malloc_internal.h"
#include "libc.h"

void	print_block_content(void *ptr_start, void *ptr_end, size_t amount_bytes) {
	const int fd = STDOUT_FILENO;

	ft_putstr_fd("0x", fd);
	ft_putnbr_base_fd((unsigned long long)ptr_start, 16, fd, true);
	ft_putstr_fd(" - 0x", fd);
	ft_putnbr_base_fd((unsigned long long)ptr_end, 16, fd, true);
	ft_putstr_fd(" : ", fd);
	ft_putnbr_base_fd((unsigned long long)amount_bytes, 10, fd, true);
	ft_putstr_fd(" bytes\n", fd);
}

// Returns the total
static size_t	show_blocks(const t_block* block) {
	size_t	total = 0;
	for (; block != NULL; block = block->next) {
		void	*ptr_start = BLOCK_SHIFT(block);
		void	*ptr_end = ptr_start + block->data_size;
		print_block_content(ptr_start, ptr_end, block->data_size);
		total += block->data_size;
	}
	return (total);
}

static void	print_zone_header(const char* str, void *zone_addr) {
	const int fd = STDOUT_FILENO;
	ft_putstr_fd(str, fd);
	ft_putstr_fd(" : ", fd);
	if (zone_addr) {
		ft_putstr_fd("0x", fd);
		ft_putnbr_base_fd((unsigned long long) zone_addr, 16, fd, true);
	}
	ft_putstr_fd("\n", fd);
}

static size_t	show_zones(const t_heap* zone, const char* str) {
	size_t	total_size = 0;
	for (const t_heap* tmp = zone; tmp; tmp = tmp->next) {
		print_zone_header(str, (void *)tmp);
		total_size += show_blocks(HEAP_SHIFT(tmp));
	}
	return (total_size);
}

static size_t	show_large_zone(const t_block *block, const char *str) {
	print_zone_header(str, (void *)block);
	return (show_blocks(block));
}

static void	print_total_bytes(const size_t total) {
	const int fd = STDOUT_FILENO;
	ft_putstr_fd("Total : ", fd);
	ft_putnbr_base_fd(total, 10, fd, true);
	ft_putstr_fd(" bytes\n", fd);
}

void	show_alloc_mem() {
	pthread_mutex_lock(&g_mutex);
	size_t	total = 0;

	total += show_zones(g_malloc_zones.tiny, "TINY");
	total += show_zones(g_malloc_zones.small, "SMALL");
	if (g_malloc_zones.large)
		total += show_large_zone(g_malloc_zones.large, "LARGE");

	print_total_bytes(total);
	pthread_mutex_unlock(&g_mutex);
}
