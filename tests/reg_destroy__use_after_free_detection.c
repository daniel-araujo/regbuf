#include <assert.h>

#include "../reg.h"

int main(int argc, char *argv[])
{
	char region[5] = {};

	struct reg_opts_region regions[] = {
		(struct reg_opts_region) {
			.buffer = region,
			.length = sizeof(region),
		}
	};

	reg_t reg = reg_create(&(struct reg_opts) {
		.regions = regions,
		.regions_length = sizeof(regions) / sizeof(regions[0])
	});

	reg_destroy(reg);

	// This is undefined behavior. Please report if it fails on your
	// platform.
	assert(reg_used(reg) == -1);

	return 0;
}