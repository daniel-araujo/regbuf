#include <assert.h>

#include "../regbuf.h"

int main(int argc, char *argv[])
{
	char first[4] = {};
	char second[4] = {};
	char third[4] = {};

	struct regbuf_opts_region regions[] = {
		(struct regbuf_opts_region) {
			.buffer = first,
			.length = sizeof(first),
		},
		(struct regbuf_opts_region) {
			.buffer = second,
			.length = 0,
		},
		(struct regbuf_opts_region) {
			.buffer = third,
			.length = sizeof(third),
		}
	};

	regbuf_t r = regbuf_create(&(struct regbuf_opts) {
		.regions = regions,
		.regions_length = sizeof(regions) / sizeof(regions[0])
	});

	assert(regbuf_error(r) != REGBUF_ERROR_NONE);

	regbuf_destroy(r);

	return 0;
}
