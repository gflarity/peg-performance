/*
 * coordinate.c
 *
 * Copyright (c) 2010, Jonathan Fuerth
 * 
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in
 *       the documentation and/or other materials provided with the
 *       distribution.
 *     * Neither the name of Jonathan Fuerth nor the names of other
 *       contributors may be used to endorse or promote products derived
 *       from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "coordinate.h"
#include "alist.h"
#include "move.h"
#include <stdlib.h>
#include <stdio.h>

coord_t *coord_new(int row, int hole) {
	coord_t *c = malloc(sizeof(coord_t));
	if (c == NULL) {
		perror("Failed to allocate coordinate");
		exit(1);
	}
	c->row = row;
	c->hole = hole;
	return c;
}

void coord_free(coord_t *c) {
	free(c);
}

alist_t *coord_possible_moves(coord_t *c, int rowCount) {
	alist_t *moves = alist_new();
	
	// upward (needs at least 2 rows above)
	if (c->row >= 3) {
		
		// up-left
		if (c->hole >= 3) {
			alist_add(moves, move_new(
							   c,
							   coord_new(c->row - 1, c->hole - 1),
							   coord_new(c->row - 2, c->hole - 2)));
		}
		
		// up-right
		if (c->row - c->hole >= 2) {
			alist_add(moves, move_new(
							   c,
							   coord_new(c->row - 1, c->hole),
							   coord_new(c->row - 2, c->hole)));
		}
	}
	
	// leftward (needs at least 2 pegs to the left)
	if (c->hole >= 3) {
		alist_add(moves, move_new(
						   c,
						   coord_new(c->row, c->hole - 1),
						   coord_new(c->row, c->hole - 2)));
	}
	
	// rightward (needs at least 2 holes to the right)
	if (c->row - c->hole >= 2) {
		alist_add(moves, move_new(
						   c,
						   coord_new(c->row, c->hole + 1),
						   coord_new(c->row, c->hole + 2)));
	}
	
	// downward (needs at least 2 rows below)
	if (rowCount - c->row >= 2) {
		
		// down-left (always possible when there are at least 2 rows below)
		alist_add(moves, move_new(
						   c,
						   coord_new(c->row + 1, c->hole),
						   coord_new(c->row + 2, c->hole)));
		
		// down-right (always possible when there are at least 2 rows below)
		alist_add(moves, move_new(
						   c,
						   coord_new(c->row + 1, c->hole + 1),
						   coord_new(c->row + 2, c->hole + 2)));
	}
	
	return moves;
}


int coord_cmp(coord_t *lhs, coord_t *rhs) {
	//printf("Compare coord r%dh%d to r%dh%d: ", lhs->row, lhs->hole, rhs->row, rhs->hole);
	if (lhs == rhs) {
		return 0;
	}
	
	if (lhs == NULL) {
		return -1;
	}
	
	if (lhs->row < rhs->row) { return -1; }
	if (lhs->row > rhs->row) { return 1; }
	
	if (lhs->hole < rhs->hole) { return -1; }
	if (lhs->hole > rhs->hole) { return 1; }
	
	return 0;
}
