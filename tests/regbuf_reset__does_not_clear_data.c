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

	const char data[] = { 1, 2, 3, 4, 5 };
	regbuf_add(r, data, sizeof(data));
	
	regbuf_reset(r);

	assert(region1[0] == 1);
	assert(region1[1] == 2);
	assert(region1[2] == 3);
	assert(region1[3] == 4);
	assert(region1[4] == 5);
	assert(region1[5] == 0);

	return 0;
}