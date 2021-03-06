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

	const char second[4];
	size_t read = regbuf_get_offset(r, second, sizeof(second), 2);

	assert(read == 2);
	assert(second[0] == 3);
	assert(second[1] == 4);

	return 0;
}