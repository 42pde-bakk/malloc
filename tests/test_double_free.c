//
// Created by Peer De bakker on 3/2/22.
//

#include <stdlib.h>
#include <stdio.h>

int	main() {
	void	*ptr = malloc(88);
	printf("ptr = %p\n", ptr);
	free(ptr);
	printf("after first free\n");
	free(ptr);
	printf("after second free\n");
	return (0);
}
