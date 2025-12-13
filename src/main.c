#include "allocator.h"

#include <stdio.h>

int
main(
    [[maybe_unused]] int   argc,
    [[maybe_unused]] char* argv[argc]
)
{
    puts("Auxilium C.");

    {
        struct Allocator allocator = allocator_basic_init();

        int* x = allocator_alloc(&allocator, sizeof(int));
        *x     = 24;
        fprintf(stdout, "*x = %d\n", *x);
        allocator_free(&allocator, x);

        allocator_basic_deinit(&allocator);
    }

    return 0;
}
