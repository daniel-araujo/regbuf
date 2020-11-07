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

	const char data[] = { 1, 2, 3, 4 };
	regbuf_add(r, data, sizeof(data));

	char buffer1[3];
	size_t read1 = regbuf_get(r, buffer1, sizeof(buffer1));

	assert(read1 == 3);
	assert(regbuf_used(r) == 1);

	char buffer2[2];
	size_t read2 = regbuf_get(r, buffer2, sizeof(buffer2));

	assert(read2 == 1);
	assert(regbuf_used(r) == 0);

	return 0;
}