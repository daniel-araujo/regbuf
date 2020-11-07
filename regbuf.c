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

#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "regbuf.h"

// Notes:
//
// The head index is positioned on the first element of the buffer. The tail
// index is positioned after the last element of the buffer, which is
// coincidentally the next place for the next element.
//
// When head and tail are in the same position, then if size is greater than 0
// this means that every region is filled. If size is 0 then no data exists.

// A handle is just a pointer to this structure.
struct regbuf_handle
{
	// Index of the region that the head is pointing to.
	size_t head_region;

	// Index in the region's memory buffer.
	size_t head_region_index;

	// Index of the region that the tail is pointing to.
	size_t tail_region;

	// Index in the region's memory buffer.
	size_t tail_region_index;

	// How much data is occupied in every region.
	size_t data_length;

	// Total number of regions in array.
	size_t regions_length;

	struct regbuf_opts_region regions[];
};

/*
 * Advances to the next region. Wraps around correctly.
 */
static inline size_t next_region(struct regbuf_handle *h, size_t current) {
	current += 1;

	if (current == h->regions_length) {
		current = 0;
	}

	return current;
}

/*
 * Returns remaining size in the current region from the given index up to
 * head index if it is in the same region.
 */
static inline size_t up_to_head(struct regbuf_handle *h, size_t region, size_t index) {
	size_t remaining;

	if (region == h->head_region) {
		// In the region where head is also.

		if (h->head_region_index < index) {
			// head is behind. We have the rest of the region for ourselves.
			remaining = h->regions[region].length - index;
		} else if (h->head_region_index == index) {
			if (h->data_length == 0) {
				// No data exists. We have the rest of the region for ourselves.
				remaining = h->regions[region].length - index;
			} else {
				// All used up. There's nothing left.
				remaining = 0;
			}
		} else {
			// Can only go up to end index.
			remaining = h->head_region_index - index;
		}
	} else {
		// The rest of the region is ours to conquer.
		remaining = h->regions[region].length - index;
	}

	return remaining;
}

/*
 * Returns remaining size in the current region from the given index up to
 * tail index if it is in the same region.
 */
static inline size_t up_to_tail(struct regbuf_handle *h, size_t region, size_t index) {
	size_t remaining;

	if (region == h->tail_region) {
		// In the region where tail is also.

		if (h->tail_region_index < index) {
			// Tail is behind. We have the rest of the region for ourselves.
			remaining = h->regions[region].length - index;
		} else if (h->tail_region_index == index) {
			if (h->data_length == 0) {
				// No data exists.
				remaining = 0;
			} else {
				// That means no space left.
				remaining = h->regions[region].length - index;
			}
		} else {
			// Can only go up to tail index.
			remaining = h->tail_region_index - index;
		}
	} else {
		// The rest of the region is ours to conquer.
		remaining = h->regions[region].length - index;
	}

	return remaining;
}

regbuf_t regbuf_create(struct regbuf_opts *opts)
{
	if (opts->regions_length == 0) {
		return NULL;
	}

	// How much memory region info takes up.
	const size_t mem_regions = opts->regions_length * sizeof(struct regbuf_opts_region);

	struct regbuf_handle *h = malloc(sizeof(struct regbuf_handle) + mem_regions);

	if (h == NULL) {
		return NULL;
	}

	h->regions_length = opts->regions_length;
	h->head_region = 0;
	h->head_region_index = 0;
	h->tail_region = 0;
	h->tail_region_index = 0;
	h->data_length = 0;

	memmove(h->regions, opts->regions, mem_regions);

	return (regbuf_t) h;
}

enum regbuf_error regbuf_error(regbuf_t handle)
{
	struct regbuf_handle *h = (struct regbuf_handle *) handle;

	if (h == NULL) {
		return regbuf_ERROR_OUT_OF_MEMORY;
	} else {
		return regbuf_ERROR_NONE;
	}
}

void regbuf_destroy(regbuf_t handle)
{
	struct regbuf_handle *h = (struct regbuf_handle *) handle;

	if (h == NULL) {
		// Must have failed to create.
		return;
	}

#ifndef NDEBUG
	// To detect use after free in debugger.
	h->data_length = -1;
#endif

	free(h);
}

size_t regbuf_add(regbuf_t handle, const void *data, size_t length)
{
	struct regbuf_handle *h = (struct regbuf_handle *) handle;

	// Offset into current data.
	size_t data_offset = 0;
	size_t data_remaining = length;

	size_t written = 0;

	while (data_remaining > 0) {
		// How much space left in the current region.
		size_t region_remaining = up_to_head(h, h->tail_region, h->tail_region_index);

		if (region_remaining == 0) {
			// No more space left in any region.
			break;
		}

		unsigned char *region_buffer = h->regions[h->tail_region].buffer;

		if (data_remaining < region_remaining) {
			// Looks like we don't have enough data to fill up
			// remaining elements in this region.
			region_remaining = data_remaining;
		}

		memcpy(region_buffer + h->tail_region_index, (char *) data + data_offset, region_remaining);

		data_offset += region_remaining;
		data_remaining -= region_remaining;

		written += region_remaining;
		h->data_length += region_remaining;
		h->tail_region_index += region_remaining;

		if (h->tail_region_index == h->regions[h->tail_region].length) {
			// Move tail to the next one.
			h->tail_region_index = 0;
			h->tail_region = next_region(h, h->tail_region);
		}
	}

	return written;
}

size_t regbuf_pop(regbuf_t handle, size_t length)
{
	struct regbuf_handle *h = (struct regbuf_handle *) handle;

	size_t removed = 0;

	while (length > 0) {
		size_t region_remaining = up_to_tail(h, h->head_region, h->head_region_index);

		if (region_remaining == 0) {
			// No more data left in any region.
			break;
		}

		if (length < region_remaining) {
			// Looks some data will remain in this region.
			region_remaining = length;
		}

		length -= region_remaining;
		removed += region_remaining;

		h->head_region_index += region_remaining;
		h->data_length -= region_remaining;

		if (h->head_region_index == h->regions[h->head_region].length) {
			// Head to the next one.
			h->head_region_index = 0;
			h->head_region = next_region(h, h->head_region);
		}
	}

	return removed;
}

size_t regbuf_get(regbuf_t handle, void *data, size_t length)
{
	struct regbuf_handle *h = (struct regbuf_handle *) handle;

	size_t retrieved = 0;

	while (length > 0) {
		size_t region_remaining = up_to_tail(h, h->head_region, h->head_region_index);

		if (region_remaining == 0) {
			// No more data left in any region.
			break;
		}

		if (length < region_remaining) {
			// Looks some data will remain in this region.
			region_remaining = length;
		}

		unsigned char *region_buffer = h->regions[h->head_region].buffer;

		memmove((char *) data + retrieved, region_buffer + h->head_region_index, region_remaining);

		length -= region_remaining;
		retrieved += region_remaining;

		h->head_region_index += region_remaining;
		h->data_length -= region_remaining;

		if (h->head_region_index == h->regions[h->head_region].length) {
			// Head to the next one.
			h->head_region_index = 0;
			h->head_region = next_region(h, h->head_region);
		}
	}

	return retrieved;
}

size_t regbuf_used(regbuf_t handle)
{
	struct regbuf_handle *h = (struct regbuf_handle *) handle;
	return h->data_length;
}