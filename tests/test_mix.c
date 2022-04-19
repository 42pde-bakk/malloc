//
// Created by Peer De bakker on 4/18/22.
//
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

int main() {
	const size_t amount = 30;
	size_t i = 0;
	void	*tiny[amount];
	void	*small[amount];
	void	*large[amount];

	while (i < amount) {
		tiny[i] = malloc(25);
		small[i] = malloc(103);
		large[i] = malloc(1012);
		i++;
	}
	i = 0;
	while (i < amount) {
		free(tiny[i]);
		free(small[i]);
		free(large[i]);
		i++;
	}
}
