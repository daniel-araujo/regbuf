#include <assert.h>

#include "../reg.h"
#include "./reg_debug.inc.c"

int main(int argc, char *argv[])
{
	char static1[5] = {};
	char static2[5] = {};

	struct reg_opts_region regions[] = {
		(struct reg_opts_region) {
			.buffer = static1,
			.length = sizeof(static1),
		},
		(struct reg_opts_region) {
			.buffer = static2,
			.length = sizeof(static2),
		}
	};

	reg_t reg = reg_create(&(struct reg_opts) {
		.regions = regions,
		.regions_length = sizeof(regions) / sizeof(regions[0])
	});

	const char first[] = { 1, 2, 3, 4 };
	reg_add(reg, first, sizeof(first));

	reg_pop(reg, 5);

	assert(reg_debug_head_region_index(reg) == 4);

	return 0;
}