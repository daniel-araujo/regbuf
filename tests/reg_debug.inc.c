#pragma once

// The purpose of this file is to provide functionality that is only useful for
// testing implementation details. Avoid as much as possible.

struct reg_debug
{
	size_t head_region;
	size_t head_region_index;
};

static size_t reg_debug_head_region_index(reg_t reg)
{
	struct reg_debug *d = (struct reg_debug *) reg;
	return d->head_region_index;
}
