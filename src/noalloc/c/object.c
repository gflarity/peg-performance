/*
 *  object.c
 *
 * Created by Jonathan Fuerth on 2010-01-12.
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

#include "object.h"
#include <stdlib.h>
#include <stdio.h>

object_t *obj_create(void *data,
					int (*compare)(void *lhs, void *rhs),
					void (*destroy)(void *data)) {
	object_t *object = malloc(sizeof(object_t));
	if (object == NULL) {
		printf("Unable to allocate an object header\n");
		exit(1);
	}
	object->refcount = 1;
	object->compare = compare;
	object->destroy = destroy;
	object->data = data;
	
	return object;
}

// increments given object's reference count
void obj_retain(object_t *object) {
	if (object->refcount <= 0) {
		printf("Reference error: attempt to retain an invalid or freed object\n");
		exit(1);
	}
	object->refcount = object->refcount + 1;
}

// decrements given object's reference count, freeing the
// object_t and its contained object if refcount becomes 0
void obj_release(object_t *object) {
	if (object->refcount <= 0) {
		printf("Reference error: attempt to release an invalid or freed object\n");
		exit(1);
	}
	object->refcount = object->refcount - 1;
	if (object->refcount == 0) {
		object->destroy(object->data);
		object->data = NULL;
		free(object);
	}
}

int obj_compare(object_t *lhs, object_t *rhs) {
	if (lhs->compare != rhs->compare) {
		printf("Null comparisons not allowed (lhs=%p, rhs=%p)\n", lhs, rhs);
		exit(1);
	}
	if (lhs->compare != rhs->compare) {
		printf("Illegal comparison attempted (objects have different compare functions)\n");
		exit(1);
	}
	return lhs->compare(lhs->data, rhs->data);
}
