#include <assert.h>

#include "../regbuf.h"

int main(int argc, char *argv[])
{
	regbuf_t r = regbuf_create(&(struct regbuf_opts) {
		.regions = NULL,
		.regions_length = 1
	});

	assert(regbuf_error(r) != REGBUF_ERROR_NONE);

	regbuf_destroy(r);

	return 0;
}
