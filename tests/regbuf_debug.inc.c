#pragma once

// The purpose of this file is to provide functionality that is only useful for
// testing implementation details. Avoid as much as possible.

struct regbuf_debug
{
	size_t head_region;
	size_t head_region_index;
};

static size_t regbuf_debug_head_region_index(regbuf_t reg)
{
	struct regbuf_debug *d = (struct regbuf_debug *) reg;
	return d->head_region_index;
}
