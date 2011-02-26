/*
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

#include <stdio.h>
#include <sys/time.h>

#include "alist.h"
#include "coordinate.h"
#include "gamestate.h"

long gamesPlayed;

// list contains lists which contain move_t*
static alist_t *solutions;

static struct timeval startTime;
static struct timeval endTime;

static void search(gamestate_t *gs, alist_t *moveStack) {
	if (gamestate_pegs_remaining(gs) == 1) {
//		printf("Found a winning sequence. Final state:\n");
//		gamestate_print(gs);
		
		alist_add(solutions, alist_new_copy(moveStack));
		
		gamesPlayed++;
		
		return;
	}
	
	alist_t *legalMoves = gamestate_legal_moves(gs);
	
	if (alist_is_empty(legalMoves)) {
		gamesPlayed++;
		return;
	}
	
	for (int i = 0; i < legalMoves->size; i++) {
		move_t *m = alist_get(legalMoves, i);
		gamestate_t *nextState = gamestate_apply_move(gs, m);
		alist_add(moveStack, m);
		search(nextState, moveStack);
		alist_remove_last(moveStack);
	}
}

static long diff_usec(struct timeval start, struct timeval end) {
	time_t secs = end.tv_sec - start.tv_sec;
	suseconds_t usecs = end.tv_usec - start.tv_usec;
	
	return (long) (secs * 1000000L) + usecs;
}

static void run() {
	solutions = alist_new();
	
	gettimeofday(&startTime, NULL);
	
	gamestate_t *gs = gamestate_new(5, coord_new(3, 2));
	search(gs, alist_new());
	
	gettimeofday(&endTime, NULL);
	
	printf("Games played:    %6ld\n", gamesPlayed);
	printf("Solutions found: %6d\n", solutions->size);
	printf("Time elapsed:    %6ldms\n", diff_usec(startTime, endTime) / 1000);
}

int main (int argc, const char * argv[]) {
	run();
    return 0;
}
