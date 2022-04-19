//
// Created by Peer De bakker on 3/2/22.
//

#include <stdlib.h>
#include "malloc.h"
#include <stdio.h>
#include <string.h>
#include <pthread.h>

static void *run_test_thread() {
	void *ret = malloc(80);
	pthread_exit(NULL);
	return ret;
}

int main() {
	const unsigned int amount = 100;
	pthread_t	*threads = malloc(sizeof(pthread_t) * amount);

	for (int i = 0; i < amount; i++) {
		if (pthread_create(&threads[i], NULL, run_test_thread, NULL)) {
			dprintf(2, "Error creating thread\n");
			return (EXIT_FAILURE);
		}
	}
	for (int i = 0; i < amount; i++) {
		if (pthread_join(threads[i], NULL)) {
			dprintf(2, "Error joining thread\n");
			return (EXIT_FAILURE);
		}
	}
	show_alloc_mem();
}
