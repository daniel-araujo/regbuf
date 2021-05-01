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

	char buffer[3];
	size_t read = regbuf_get_offset(r, buffer, sizeof(buffer), 3);

	assert(read == 3);
	assert(buffer[0] == 4);
	assert(buffer[1] == 5);
	assert(buffer[2] == 6);

	return 0;
}