#include <assert.h>

#include "../regbuf.h"

int main(int argc, char *argv[])
{
	char region[3] = {};

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

	assert(regbuf_free(r) == regbuf_total(r));

	return 0;
}