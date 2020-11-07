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

	const char data1[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	reg_add(reg, data1, sizeof(data1));

	reg_pop(reg, 1);

	const char data2[] = { 11 };
	size_t added = reg_add(reg, data2, sizeof(data2));

	assert(added == 1);

	assert(region1[0] == 11);
	assert(region1[1] == 2);
	assert(region1[2] == 3);
	assert(region1[3] == 4);
	assert(region1[4] == 5);

	assert(region2[0] == 6);
	assert(region2[1] == 7);
	assert(region2[2] == 8);
	assert(region2[3] == 9);
	assert(region2[4] == 10);

	return 0;
}