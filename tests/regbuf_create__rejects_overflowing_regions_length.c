#include <assert.h>
#include <stdint.h>

#include "../regbuf.h"

int main(int argc, char *argv[])
{
	char buffer[4] = {};

	struct regbuf_opts_region regions[] = {
		(struct regbuf_opts_region) {
			.buffer = buffer,
			.length = sizeof(buffer),
		}
	};

	regbuf_t r = regbuf_create(&(struct regbuf_opts) {
		.regions = regions,
		.regions_length = SIZE_MAX
	});

	assert(regbuf_error(r) != REGBUF_ERROR_NONE);

	regbuf_destroy(r);

	return 0;
}
