#include <assert.h>

#include "../regbuf.h"

int main(int argc, char *argv[])
{
	char region1[5] = {};
	char region2[5] = {};

	struct regbuf_opts_region regions[] = {
		(struct regbuf_opts_region) {
			.buffer = region1,
			.length = sizeof(region1),
		},
		(struct regbuf_opts_region) {
			.buffer = region2,
			.length = sizeof(region2),
		}
	};

	regbuf_t r = regbuf_create(&(struct regbuf_opts) {
		.regions = regions,
		.regions_length = sizeof(regions) / sizeof(regions[0])
	});

	const char data[] = { 1, 2, 3, 4, 5, 6, 7 };
	regbuf_add(r, data, sizeof(data));

	char buffer1[3];
	size_t read1 = regbuf_get(r, buffer1, sizeof(buffer1));

	assert(read1 == 3);

	regbuf_pop(r, sizeof(buffer1));

	assert(regbuf_total_used(r) == 4);

	char buffer2[4];
	size_t read2 = regbuf_get(r, buffer2, sizeof(buffer2));

	assert(read2 == 4);

	regbuf_pop(r, sizeof(buffer2));

	assert(regbuf_total_used(r) == 0);

	assert(buffer2[0] == 4);
	assert(buffer2[1] == 5);
	assert(buffer2[2] == 6);
	assert(buffer2[3] == 7);

	return 0;
}