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

	const char data[] = { 1, 2, 3, 4, 5 };
	reg_add(reg, data, sizeof(data));

	char buffer1[3];
	size_t read1 = reg_get(reg, buffer1, sizeof(buffer1));

	assert(read1 == 3);

	assert(buffer1[0] == 1);
	assert(buffer1[1] == 2);
	assert(buffer1[2] == 3);

	char buffer2[2];
	size_t read2 = reg_get(reg, buffer2, sizeof(buffer2));

	assert(read2 == 2);

	assert(buffer2[0] == 4);
	assert(buffer2[1] == 5);

	return 0;
}