#include <assert.h>

#include "../reg.h"

int main(int argc, char *argv[])
{
	char region1[3] = {};
	char region2[3] = {};

	struct reg_opts_region regions[] = {
		(struct reg_opts_region) {
			.buffer = region1,
			.length = sizeof(region1),
		},
		(struct reg_opts_region) {
			.buffer = region2,
			.length = sizeof(region2),
		}
	};

	reg_t reg = reg_create(&(struct reg_opts) {
		.regions = regions,
		.regions_length = sizeof(regions) / sizeof(regions[0])
	});

	const char data1[] = { 1, 2, 3, 4, 5, 6 };
	reg_add(reg, data1, sizeof(data1));

	reg_pop(reg, 3);

	const char data2[] = { 7, 8, 9 };
	reg_add(reg, data2, sizeof(data2));

	char buffer[6];
	size_t read = reg_get(reg, buffer, sizeof(buffer));

	assert(read == 6);

	assert(buffer[0] == 4);
	assert(buffer[1] == 5);
	assert(buffer[2] == 6);
	assert(buffer[3] == 7);
	assert(buffer[4] == 8);
	assert(buffer[5] == 9);

	return 0;
}