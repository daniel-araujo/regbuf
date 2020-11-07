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
		}
	};

	reg_t reg = reg_create(&(struct reg_opts) {
		.regions = regions,
		.regions_length = sizeof(regions) / sizeof(regions[0])
	});

	const char data[] = { 1, 2, 3, 4 };
	reg_add(reg, data, sizeof(data));

	char buffer[4] = {};
	size_t read = reg_get(reg, buffer, 0);

	assert(read == 0);

	assert(reg_used(reg) == 4);
	
	assert(buffer[0] == 0);
	assert(buffer[1] == 0);
	assert(buffer[2] == 0);
	assert(buffer[3] == 0);

	return 0;
}