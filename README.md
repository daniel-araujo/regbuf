# Regbuf

A ring buffer that spans over multiple regions in portable C code. Useful in
memory constrained environments with multiple memory regions.


## How to use

Just copy `regbuf.c` and `regbuf.h` into your project and compile.

You can safely include the header file in your C++ code.

```c
#include <stdio.h>
#include <stdlib.h>

#include "regbuf.h"

char static_mem_region[10] = {};

int main(int argc, char *argv[])
{
	char *dynamic_mem_region = malloc(10);

	struct regbuf_opts_region regions[] = {
		(struct regbuf_opts_region) {
			.buffer = static_mem_region,
			.length = sizeof(static_mem_region),
		},
		(struct regbuf_opts_region) {
			.buffer = dynamic_mem_region,
			.length = 10,
		},
	};

	regbuf_t r = regbuf_create(&(struct regbuf_opts) {
		.regions = regions,
		.regions_length = 2
	});

	const char input[] = "Hello, world!\n";
	regbuf_add(r, input, sizeof(input));

	char output[20] = {};
	regbuf_get(r, output, sizeof(output));

	puts(output);

	regbuf_destroy(r);
	free(dynamic_mem_region);

	return 0;
}
```


## Documentation

Read `reg.h`. The comments will explain everything.


## License

Fuck around and find out. Read LICENSE file for details.
