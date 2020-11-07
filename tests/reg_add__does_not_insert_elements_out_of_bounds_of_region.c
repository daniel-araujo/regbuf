#include <assert.h>

#include "../reg.h"

int main(int argc, char *argv[])
{
	// Reserving more space than we declare to reg so we can check for out
	// of bounds access.
	char region[6] = {};

	struct reg_opts_region regions[] = {
		(struct reg_opts_region) {
			.buffer = region,
			.length = sizeof(region) - 1,
		}
	};

	reg_t reg = reg_create(&(struct reg_opts) {
		.regions = regions,
		.regions_length = sizeof(regions) / sizeof(regions[0])
	});

	const char first[] = { 1, 2, 3, 4, 5, 6 };
	size_t added = reg_add(reg, first, sizeof(first));

	assert(added == 5);

	assert(region[0] == 1);
	assert(region[1] == 2);
	assert(region[2] == 3);
	assert(region[3] == 4);
	assert(region[4] == 5);

	// Sanity check.
	assert(region[5] == 0);

	return 0;
}