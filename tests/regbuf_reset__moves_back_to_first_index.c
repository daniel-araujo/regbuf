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

	const char data1[] = { 1, 2 };
	regbuf_add(r, data1, sizeof(data1));
	
	regbuf_reset(r);

	const char data2[] = { 3 };
	regbuf_add(r, data2, sizeof(data2));

	assert(region[0] == 3);

	return 0;
}