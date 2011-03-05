/*
 *  memory.c
 *  performance_c
 *
 *  Created by Jonathan Fuerth on 2010-02-05.
 */

#include "memory.h"
#include <stdio.h>
#include <stdlib.h>

#define ALLOC_MAGIC 0xDEAFB00B

#ifdef DEBUG_MEMORY
static int freed_allocations = 0;
static int total_allocations = 0;

// linked list of allocation info
typedef struct alloc_info {
	int allocations;
	const char *type;
	struct alloc_info *next;
} alloc_info_t;

static alloc_info_t *first_alloc_info = NULL;

static alloc_info_t *get_alloc_info(const char *type) {
	alloc_info_t *ai = first_alloc_info;
	while (ai != NULL) {
		if (ai->type == type) break;
		ai = ai->next;
	}
	
	// if not found, create a new one
	if (ai == NULL) {
		ai = malloc(sizeof(alloc_info_t));
		if (ai == NULL) {
			perror("Failed to malloc an alloc_info");
			exit(1);
		}
		
		ai->type = type;
		ai->allocations = 0;
		ai->next = first_alloc_info; // will be NULL for first ai created
		
		first_alloc_info = ai;
	}
	
	return ai;
}
#endif

typedef struct alloc_header {
	int magic;
	int references;
	void (*destructor)(void *);
	const char *type;
} alloc_header_t;

void *mem_alloc(size_t size, void (*destructor)(void *), const char *type) {
	void *mem = malloc(sizeof(alloc_header_t) + size);
	if (mem == NULL) {
		perror("Failed to allocate some memory");
		exit(1);
	}
	
	alloc_header_t *ah = mem;
	ah->magic = ALLOC_MAGIC;
	ah->references = 1;
	ah->destructor = destructor;
	ah->type = type;

#ifdef DEBUG_MEMORY
	alloc_info_t *ai = get_alloc_info(type);
	ai->allocations = ai->allocations + 1;
	
	total_allocations++;
#endif
	
	return mem + sizeof(alloc_header_t);
}

void mem_retain(void *addr) {
	void *headerptr = addr - sizeof(alloc_header_t);
	alloc_header_t *ah = headerptr;
	if (ah->magic != ALLOC_MAGIC) {
		fprintf(stderr, "Yikes, bad magic: %x", ah->magic);
		exit(1);
	}
	
	ah->references = ah->references + 1;
}


void mem_release(void *addr) {
	void *headerptr = addr - sizeof(alloc_header_t);
	alloc_header_t *ah = headerptr;
	if (ah->magic != ALLOC_MAGIC) {
		fprintf(stderr, "Yikes, bad magic: %x", ah->magic);
		exit(1);
	}
	
	ah->references = ah->references - 1;
	if (ah->references == 0) {
		ah->destructor(addr);
		ah->magic = 0xF5EED;
		
#ifdef DEBUG_MEMORY
		alloc_info_t *ai = get_alloc_info(ah->type);
		ai->allocations = ai->allocations - 1;

		freed_allocations++;
#endif
		
		free(ah);
	}
}

void mem_summary() {
#ifdef DEBUG_MEMORY
	printf("Memory allocation summary:\n");
	printf("Total count of objects allocated:   %8d\n", total_allocations);
	printf("Of those, number of objects freed:  %8d\n", freed_allocations);
	printf("Remaining live allocations (leaks): %8d\n", total_allocations - freed_allocations);
	alloc_info_t *ai = first_alloc_info;
	while (ai != NULL) {
		printf("   Remaining allocations for %10s: %8d\n", ai->type, ai->allocations); 
		ai = ai->next;
	}
#else
	printf("Memory debugging was disabled at compile time.\n");
#endif
}
