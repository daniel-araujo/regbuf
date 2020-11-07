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

	const char data[] = { 1, 2, 3, 4, 5, 6, 7 };
	reg_add(reg, data, sizeof(data));

	char buffer1[3];
	size_t read1 = reg_get(reg, buffer1, sizeof(buffer1));

	assert(read1 == 3);
	assert(reg_used(reg) == 4);

	char buffer2[4];
	size_t read2 = reg_get(reg, buffer2, sizeof(buffer2));

	assert(read2 == 4);
	assert(reg_used(reg) == 0);
	assert(buffer2[0] == 4);
	assert(buffer2[1] == 5);
	assert(buffer2[2] == 6);
	assert(buffer2[3] == 7);

	return 0;
}