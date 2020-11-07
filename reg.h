// Reg release 1
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

struct reg_opts_region {
	// Pointer to buffer.
	void *buffer;

	// Length of buffer in bytes.
	size_t length;
};

// Options for creating a reg handle.
struct reg_opts
{
	// Pointer to array of regions.
	struct reg_opts_region *regions;

	// Number of regions in array.
	size_t regions_length;
};

enum reg_error
{
	REG_ERROR_NONE = 0,
	REG_ERROR_OUT_OF_MEMORY = 1,
};

// Do not look at this.
typedef struct { int reg; } *reg_t;

/*
 * See options struct for more details.
 *
 * The handle is not thread-safe. Synchronization between threads is up to you.
 *
 * You must call reg_error to check if the handle was successfully created. if
 * the handle failed to be created correctly then you can only pass it to
 * reg_error and reg_destroy. Any other functions will result in undefined
 * behavior.
 */
reg_t reg_create(struct reg_opts *opts);

/*
 * Disposes resources. The handle can no longer be used after calling this
 * method.
 */
void reg_destroy(reg_t handle);

/*
 * Checks if handle is still usable. If this returns a value other than
 * REG_ERROR_NONE then you should destroy the handle.
 */
enum reg_error reg_error(reg_t handle);

/*
 * Adds data. Returns length added, starting from the first index of data.
 */
size_t reg_add(reg_t handle, const void *data, size_t length);

/**
 * Retrieves data from the buffer. Returns actual length written to data.
 */
size_t reg_get(reg_t handle, void *data, size_t length);

/*
 * Removes oldest data from buffer. Returns actual length removed.
 */
size_t reg_pop(reg_t handle, size_t length);

/*
 * Reports how much space is used.
 */
size_t reg_used(reg_t handle);

#ifdef __cplusplus
}
#endif
