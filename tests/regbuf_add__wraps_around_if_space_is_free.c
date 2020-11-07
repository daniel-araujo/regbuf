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

	const char data1[] = { 1, 2, 3, 4, 5 };
	regbuf_add(r, data1, sizeof(data1));

	regbuf_pop(r, 1);

	const char data2[] = { 6 };
	size_t added = regbuf_add(r, data2, sizeof(data2));

	assert(added == 1);

	assert(region[0] == 6);
	assert(region[1] == 2);
	assert(region[2] == 3);
	assert(region[3] == 4);
	assert(region[4] == 5);

	return 0;
}