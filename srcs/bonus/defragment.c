//
// Created by Peer De bakker on 3/1/22.
//

#include "peer_stdlib.h"

//static void	combine_blocks(t_block *first, t_block *second) {
//	first->next = second->next;
//	first->next->prev = first; // re-linked blocks
//	first->data_size += sizeof(t_block) + second->data_size;
//}
//
//void	declutter_freed_areas(t_block *block) {
//	// Wait, is this bonus?
//
//	if (block->next && block->next->status == FREED)
//		combine_blocks(block, block->next);
//	if (block->prev && block->prev->status == FREED) {
//		combine_blocks(block->prev, block);
//		block = block->prev;
//	}
//	if (!block->next) {
//		// Is it wise to give this block back to the zone?
//		block->prev->next = NULL;
//	}
//}
