#include <assert.h>

#include "../reg.h"

int main(int argc, char *argv[])
{
	char region1[3] = {};
	char region2[3] = {};

	// Reserving more space than we declare to reg so we can check for out
	// of bounds access.
	char region3[4] = {};

	struct reg_opts_region regions[] = {
		(struct reg_opts_region) {
			.buffer = region1,
			.length = sizeof(region1),
		},
		(struct reg_opts_region) {
			.buffer = region2,
			.length = sizeof(region2),
		},
		(struct reg_opts_region) {
			.buffer = region3,
			.length = sizeof(region3) - 1,
		}
	};

	reg_t reg = reg_create(&(struct reg_opts) {
		.regions = regions,
		.regions_length = sizeof(regions) / sizeof(regions[0])
	});

	const char first[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	size_t added = reg_add(reg, first, sizeof(first));

	assert(added == 9);

	assert(region1[0] == 1);
	assert(region1[1] == 2);
	assert(region1[2] == 3);

	assert(region2[0] == 4);
	assert(region2[1] == 5);
	assert(region2[2] == 6);

	assert(region3[0] == 7);
	assert(region3[1] == 8);
	assert(region3[2] == 9);

	// Sanity check.
	assert(region3[3] == 0);

	return 0;
}