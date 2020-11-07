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

	const char data1[] = { 1, 2, 3, 4, 5 };
	reg_add(reg, data1, sizeof(data1));

	reg_pop(reg, 1);

	const char data2[] = { 6 };
	size_t added = reg_add(reg, data2, sizeof(data2));

	assert(added == 1);

	assert(region[0] == 6);
	assert(region[1] == 2);
	assert(region[2] == 3);
	assert(region[3] == 4);
	assert(region[4] == 5);

	return 0;
}