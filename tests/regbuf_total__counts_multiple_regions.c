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

	assert(regbuf_total(r) == 6);

	return 0;
}