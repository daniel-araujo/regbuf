#include <assert.h>

#include "../regbuf.h"

int main(int argc, char *argv[])
{
	char region[5] = {};

	struct regbuf_opts_region regions[] = {
		(struct regbuf_opts_region) {
			.buffer = region,
			.length = sizeof(region),
		}
	};

	regbuf_t r = regbuf_create(&(struct regbuf_opts) {
		.regions = regions,
		.regions_length = sizeof(regions) / sizeof(regions[0])
	});

	const char first[] = { 1, 2 };
	size_t added1 = regbuf_add(r, first, sizeof(first));

	assert(added1 == 2);

	const char second[] = { 3, 4 };
	size_t added2 = regbuf_add(r, second, sizeof(second));

	assert(added2 == 2);

	assert(region[0] == 1);
	assert(region[1] == 2);
	assert(region[2] == 3);
	assert(region[3] == 4);

	return 0;
}