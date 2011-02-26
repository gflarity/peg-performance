/*
 * alist.h
 *
 * Created by Jonathan Fuerth on 2010-01-04.
 *
 * Provides the subset of Java's ArrayList features which
 * are required for the performance tests.
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

#ifndef __ALIST_H__
#define __ALIST_H__

typedef struct alist {
	int size;
	int capacity;
	void **entries;
} alist_t;

alist_t *alist_new();
alist_t *alist_new_sized(int initial_capacity);
alist_t *alist_new_copy(alist_t *src);
void alist_free(alist_t *list);

void alist_add(alist_t *list, void *item);
void alist_remove_at(alist_t *list, int idx);

/* Returns 1 if item was removed; 0 if item was not found */
int alist_remove(alist_t *list, void *item, int (*comparator)(void *, void *));

void alist_remove_last(alist_t *list);
void *alist_get(alist_t *list, int idx);
int alist_contains(alist_t *list, void *item, int (*comparator)(void *, void *));
int alist_index_of(alist_t *list, void *item, int (*comparator)(void *, void *));
int alist_size(alist_t *list);
int alist_is_empty(alist_t *list);

#endif
