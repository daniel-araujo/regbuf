#include <assert.h>

#include "../regbuf.h"
#include "./regbuf_debug.inc.c"

int main(int argc, char *argv[])
{
	char buffer[4] = {};

	struct regbuf_opts_region regions[] = {
		(struct regbuf_opts_region) {
			.buffer = buffer,
			.length = sizeof(buffer),
		}
	};

	regbuf_t r = regbuf_create(&(struct regbuf_opts) {
		.regions = regions,
		.regions_length = sizeof(regions) / sizeof(regions[0])
	});

	const char first[] = { 1, 2, 3, 4 };
	regbuf_add(r, first, sizeof(first));
	regbuf_pop(r, 2);

	char third[4];
	size_t read = regbuf_get_offset(r, third, sizeof(third), 4);

	assert(read == 0);

	return 0;
}