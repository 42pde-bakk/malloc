//
// Created by Peer De bakker on 4/20/22.
//

#include "malloc_internal.h"
#include <stdlib.h>

unsigned int get_log_level(const t_loglevel lvl) {
	static int once = 1;
	static unsigned int env = 0;

	if (once) {
		once = 0;
		if (getenv("MALLOC_LOG_ALLOCS"))
			env |= LOG_ALLOCS;
		if (getenv("MALLOC_LOG_CALLS"))
			env |= LOG_CALLS;
	}
	return (env & lvl);
}
