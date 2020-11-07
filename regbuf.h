// Regbuf release 1
//
// copyright (c) 2020 Daniel Araujo
//
// permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "software"), to deal
// in the software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the software, and to permit persons to whom the software is
// furnished to do so, subject to the following conditions:
//
// the above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the software.
//
// the software shall be used for Good, not Evil. the original author of the
// software retains the sole and exclusive right to determine which uses are
// Good and which uses are Evil.
//
// the software is provided "as is", without warranty of any kind, express or
// implied, including but not limited to the warranties of merchantability,
// fitness for a particular purpose and noninfringement. in no event shall the
// authors or copyright holders be liable for any claim, damages or other
// liability, whether in an action of contract, tort or otherwise, arising from,
// out of or in connection with the software or the use or other dealings in the
// software.

#pragma once

// For size_t.
#include <stdlib.h>

// This allows this header to be included in C++ sources files.
#ifdef __cplusplus
extern "C" {
#endif

struct regbuf_opts_region {
	// Pointer to buffer.
	void *buffer;

	// Length of buffer in bytes.
	size_t length;
};

// Options for creating a reg handle.
struct regbuf_opts
{
	// Pointer to array of regions.
	struct regbuf_opts_region *regions;

	// Number of regions in array.
	size_t regions_length;
};

enum regbuf_error
{
	regbuf_ERROR_NONE = 0,
	regbuf_ERROR_OUT_OF_MEMORY = 1,
};

// Do not look at this.
typedef struct { int reg; } *regbuf_t;

/*
 * See options struct for more details.
 *
 * The handle is not thread-safe. Synchronization between threads is up to you.
 *
 * You must call regbuf_error to check if the handle was successfully created. if
 * the handle failed to be created correctly then you can only pass it to
 * regbuf_error and regbuf_destroy. Any other functions will result in undefined
 * behavior.
 */
regbuf_t regbuf_create(struct regbuf_opts *opts);

/*
 * Disposes resources. The handle can no longer be used after calling this
 * method.
 */
void regbuf_destroy(regbuf_t handle);

/*
 * Checks if handle is still usable. If this returns a value other than
 * regbuf_ERROR_NONE then you should destroy the handle.
 */
enum regbuf_error regbuf_error(regbuf_t handle);

/*
 * Adds data. Returns length added, starting from the first index of data.
 */
size_t regbuf_add(regbuf_t handle, const void *data, size_t length);

/*
 * Retrieves data from the buffer. Returns actual length written to data.
 */
size_t regbuf_get(regbuf_t handle, void *data, size_t length);

/*
 * Removes oldest data from buffer. Returns actual length removed.
 */
size_t regbuf_pop(regbuf_t handle, size_t length);

/*
 * Forgets tracked elements. Pointers go back to the start.
 */
void regbuf_reset(regbuf_t handle);

/*
 * Reports number of elements that can be placed over all regions: total space.
 */
size_t regbuf_total(regbuf_t handle);

/*
 * Reports number of elements that can be retrieved: used space.
 */
size_t regbuf_total_used(regbuf_t handle);

/*
 * Reports how many elements can be added: free space.
 */
size_t regbuf_total_free(regbuf_t handle);

#ifdef __cplusplus
}
#endif
