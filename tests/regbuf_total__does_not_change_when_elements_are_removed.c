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

	const char data[] = { 1, 2, 3, 4 };
	regbuf_add(r, data, sizeof(data));

	regbuf_pop(r, 2);

	assert(regbuf_total(r) == 3);

	return 0;
}