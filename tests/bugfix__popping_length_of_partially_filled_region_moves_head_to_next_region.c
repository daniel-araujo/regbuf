#include <assert.h>

#include "../regbuf.h"
#include "./regbuf_debug.inc.c"

int main(int argc, char *argv[])
{
	char static1[5] = {};
	char static2[5] = {};

	struct regbuf_opts_region regions[] = {
		(struct regbuf_opts_region) {
			.buffer = static1,
			.length = sizeof(static1),
		},
		(struct regbuf_opts_region) {
			.buffer = static2,
			.length = sizeof(static2),
		}
	};

	regbuf_t r = regbuf_create(&(struct regbuf_opts) {
		.regions = regions,
		.regions_length = sizeof(regions) / sizeof(regions[0])
	});

	const char first[] = { 1, 2, 3, 4 };
	regbuf_add(r, first, sizeof(first));

	regbuf_pop(r, 5);

	assert(regbuf_debug_head_region_index(r) == 4);

	return 0;
}