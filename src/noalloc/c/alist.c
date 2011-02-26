/*
 *  alist.c
 *
 * Created by Jonathan Fuerth on 2010-01-04.
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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "alist.h"

static void ensure_capacity(alist_t *list, int capacity) {
	if (capacity > list->capacity) {
		void *new_ents = realloc(list->entries, sizeof(void *) * capacity);
		if (new_ents == NULL) {
			perror("Failed to resize arraylist");
			exit(1);
		}
		list->entries = new_ents;
		list->capacity = capacity;
	}
}

alist_t *alist_new() {
	return alist_new_sized(10);
}

alist_t *alist_new_sized(int initial_capacity) {
	alist_t *alist = malloc(sizeof(alist_t));
	if (alist == NULL) {
		perror("Failed to allocate arraylist control block");
		exit(1);
	}
	
	alist->capacity = 0;
	alist->size = 0;
	alist->entries = NULL;
	
	ensure_capacity(alist, initial_capacity);
	
	return alist;
}

alist_t *alist_new_copy(alist_t *src) {
	alist_t *alist = malloc(sizeof(alist_t));
	if (alist == NULL) {
		perror("Failed to allocate arraylist control block");
		exit(1);
	}
	
	alist->capacity = 0;
	alist->size = src->size;
	alist->entries = NULL;
	
	ensure_capacity(alist, src->capacity);
	memmove(alist->entries, src->entries, sizeof(void *) * src->size);
	
	return alist;
}

void alist_free(alist_t *list) {
	free(list->entries);
	free(list);
}

void alist_add(alist_t *list, void *item) {
	ensure_capacity(list, list->size + 1);
	list->entries[list->size] = item;
	list->size = list->size + 1;
}

// 0 1 2 3 4 5 6  -- size == 7
// remove 1
// 0 2 3 4 5 6    -- 5 items starting at 2 (5 == size - startidx)
void alist_remove_at(alist_t *list, int idx) {
	if (idx < 0 || idx >= list->size) {
		printf("alist_remove_at: index out of bounds. idx=%d; size=%d\n", idx, list->size);
		exit(1);
	}
	
	//memmove(list->entries + idx, list->entries + idx + 1, list->size - (idx + 1));
	for (int i = idx; i < (list->size - 1); i++) {
		list->entries[i] = list->entries[i + 1];
	}
	list->size = list->size - 1;
	list->entries[list->size] = NULL;
}

/* Returns 1 if item was removed; 0 if item was not found */
int alist_remove(alist_t *list, void *item, int (*comparator)(void *, void *)) {
	int idx = alist_index_of(list, item, comparator);
	if (idx >= 0) {
		alist_remove_at(list, idx);
		return 1;
	} else {
		return 0;
	}
}

void alist_remove_last(alist_t *list) {
	list->size = list->size - 1;
	list->entries[list->size] = NULL;
}

void *alist_get(alist_t *list, int idx) {
	if (idx >= list->size || idx < 0) {
		printf("Out-of-bounds list access. idx=%d; size=%d\n", idx, list->size);
		exit(1);
	}
	return list->entries[idx];
}

int alist_contains(alist_t *list, void *item, int (*comparator)(void *, void *)) {
	return alist_index_of(list, item, comparator) != -1;
}

int alist_index_of(alist_t *list, void *item, int (*comparator)(void *, void *)) {
	for (int i = 0; i < list->size; i++) {
		if (comparator(item, list->entries[i]) == 0) {
			return i;
		}
	}
	return -1;
}

int alist_size(alist_t *list) {
	return list->size;
}

int alist_is_empty(alist_t *list) {
	return list->size == 0;
}
