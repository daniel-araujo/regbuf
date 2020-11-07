#include <assert.h>

#include "../regbuf.h"

int main(int argc, char *argv[])
{
	char region1[3] = {};
	char region2[3] = {};

	struct regbuf_opts_region regions[] = {
		(struct regbuf_opts_region) {
			.buffer = region1,
			.length = sizeof(region1),
		},
		(struct regbuf_opts_region) {
			.buffer = region2,
			.length = sizeof(region2),
		},
	};

	regbuf_t r = regbuf_create(&(struct regbuf_opts) {
		.regions = regions,
		.regions_length = sizeof(regions) / sizeof(regions[0])
	});

	const char data[] = { 1, 2 };
	size_t added = regbuf_add(r, data, sizeof(data));

	assert(added == 2);

	assert(region1[0] == 1);
	assert(region1[1] == 2);
	assert(region1[2] == 0);

	assert(region2[0] == 0);
	assert(region2[1] == 0);
	assert(region2[2] == 0);

	return 0;
}