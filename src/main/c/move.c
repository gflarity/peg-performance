/*
 *  move.c
 *
 * Created by Jonathan Fuerth on 2010-01-05.
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

#include "memory.h"
#include "move.h"
#include <stdlib.h>
#include <stdio.h>

static void move_free(move_t *m) {
	mem_release(m->from);
	mem_release(m->jumped);
	mem_release(m->to);
}

move_t *move_new(coord_t *from, coord_t *jumped, coord_t *to) {
	move_t *m = mem_alloc(sizeof(move_t), move_free, "move");

	m->from = from;
	mem_retain(from);
	
	m->jumped = jumped;
	mem_retain(jumped);
	
	m->to = to;
	mem_retain(to);
	
	return m;
}

int move_cmp(move_t *lhs, move_t *rhs) {
	if (lhs == rhs)
		return 0;
	if (lhs == NULL)
		return -1;
	
	int diff;
	
	diff = coord_cmp(lhs->from, rhs->from);
	if (diff != 0) {
		return diff;
	}
	
	diff = coord_cmp(lhs->jumped, rhs->jumped);
	if (diff != 0) {
		return diff;
	}
	
	diff = coord_cmp(lhs->to, rhs->to);
	if (diff != 0) {
		return diff;
	}
	
	return 0;
}

void move_print(move_t *move) {
	printf("r%dh%d -> r%dh%d -> r%dh%d\n",
		   move->from->row,   move->from->hole,
		   move->jumped->row, move->jumped->hole,
		   move->to->row,     move->to->hole); 
}

