/*
 *  memory.h
 *  performance_c
 *
 *  Created by Jonathan Fuerth on 2010-02-05.
 */

#ifndef __MEMORY_H__
#define __MEMORY_H__

#include <stdlib.h>

// allocates size bytes of memory and returns the address of the first byte.
// Note that some additional memory is allocated for accounting purposes,
// but this extra overhead is not for use by the caller.
//
// The second argument is a pointer to a function that releases resources
// referenced by the allocated object. This function will be called once per
// allocated object, when mem_release() decreases that object's refcount to 0.
// The function should NOT free the pointer passed to it--it should just free
// resources held by the object itself.
//
// The third argument is a pointer to a string naming the type of the object
// this allocation is for. This information is only used as an aid in debugging.
// For this system to be helpful, be sure to pass in exactly the same pointer
// every time you allocate the same object. See mem_summary() for details.
// 
// Memory allocated using mem_alloc() must be released by a call to
// mem_release() with exactly the same address as was returned by this function.
//
// This function never returns NULL. If there is not enough memory to satisfy
// the request, the whole program will exit.
void *mem_alloc(size_t size, void (*destructor)(void *), const char *type);

// Increases the reference count for the given block of memory.
// addr must be an address previously returned by mem_alloc().
void mem_retain(void *addr);

// Decreases the reference count for the given block of memory.
// If this causes the reference count to drop to 0, the memory block is
// freed for reuse by future allocations.
// addr must be an address previously returned by mem_alloc().
void mem_release(void *addr);

// Prints a summary of how many allocations have happened, how many were
// subsequently freed, and how many remain unfreed.
void mem_summary();

#endif
