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
	const char second[] = { 5, 6 };
	regbuf_add(r, second, sizeof(second));

	const char third[4];
	size_t read = regbuf_get_offset(r, third, sizeof(third), 2);

	assert(read == 2);
	assert(third[0] == 5);
	assert(third[1] == 6);

	return 0;
}