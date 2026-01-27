#include "auxilium.h"

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
        *x = 24;
        allocator_free(&allocator, x);
        x = nullptr;

        int* ints = nullptr;
        dynamic_array_init(int, &allocator, 3, &ints);

        dynamic_array_push(&ints, 12);
        dynamic_array_push(&ints, 21);
        dynamic_array_push(&ints, 55);
        dynamic_array_push(&ints, 70);

        for (int i = 0; i < dynamic_array_length(ints); ++i)
        {
            printf("ints[%d] = %d;\n", i, ints[i]);
        }

        dynamic_array_deinit((void**)&ints);

        allocator_basic_deinit(&allocator);
    }

    return 0;
}
