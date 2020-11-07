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

	const char data1[] = { 1, 2, 3, 4, 5, 6 };
	regbuf_add(r, data1, sizeof(data1));

	regbuf_pop(r, 3);

	const char data2[] = { 7, 8, 9 };
	regbuf_add(r, data2, sizeof(data2));

	int removed = regbuf_pop(r, 6);

	assert(removed == 6);

	const char data3[] = { 10 };
	regbuf_add(r, data3, sizeof(data3));

	assert(region2[0] == 10);

	return 0;
}