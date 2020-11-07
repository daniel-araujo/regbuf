#include <assert.h>

#include "../reg.h"

int main(int argc, char *argv[])
{
	char region1[5] = {};
	char region2[5] = {};

	struct reg_opts_region regions[] = {
		(struct reg_opts_region) {
			.buffer = region1,
			.length = sizeof(region1),
		},
		(struct reg_opts_region) {
			.buffer = region2,
			.length = sizeof(region2),
		},
	};

	reg_t reg = reg_create(&(struct reg_opts) {
		.regions = regions,
		.regions_length = sizeof(regions) / sizeof(regions[0])
	});

	const char data1[] = { 1, 2 };
	size_t added1 = reg_add(reg, data1, sizeof(data1));

	assert(added1 == 2);

	const char data2[] = { 3, 4, 5, 6 };
	size_t added2 = reg_add(reg, data2, sizeof(data2));

	assert(added2 == 4);

	assert(region1[0] == 1);
	assert(region1[1] == 2);
	assert(region1[2] == 3);
	assert(region1[3] == 4);
	assert(region1[4] == 5);

	assert(region2[0] == 6);

	return 0;
}