/**
 * @file basic_allocator.c
 * @author Vele Dan Alexandru (vele.dan.alexandru@gmail.com)
 * @brief A basic allocator that wraps malloc/realloc/free and counts the
 * allocations.
 * @version 0.1
 * @date 2025-10-16
 *
 */

#include "allocator.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief A basic allocator just a wrapper over defautl malloc/realloc/free that
 * keeps track of the number of allocations.
 *
 */
struct AllocatorBasic
{
    size_t allocations;
};

// ----------------------------------------------------------------------------
// Private methods ------------------------------------------------------------
// ----------------------------------------------------------------------------
#pragma region PrivateMethods

void*
allocator_basic_alloc(
    const struct Allocator* allocator,
    size_t                  size
)
{
    struct AllocatorBasic* self = allocator->handle;
    void*                  allocation = malloc(size);

    if (allocation != nullptr)
    {
        self->allocations += 1;
    }

    return allocation;
}

void*
allocator_basic_realloc(
    [[maybe_unused]] const struct Allocator* allocator,
    void*                                    ptr,
    size_t                                   size
)
{
    // struct AllocatorBasic* self = allocator->handle;
    void* reallocation = realloc(ptr, size);

    return reallocation;
}

void
allocator_basic_free(
    const struct Allocator* allocator,
    void*                   ptr
)
{
    struct AllocatorBasic* self = allocator->handle;
    self->allocations -= 1;

    free(ptr);
}

#pragma endregion PrivateMethods

// ----------------------------------------------------------------------------
// Public methods -------------------------------------------------------------
// ----------------------------------------------------------------------------
#pragma region PublicMethods

struct Allocator
allocator_basic_init(
    void
)
{
    struct Allocator self = (struct Allocator) {
        .handle = malloc(sizeof(struct AllocatorBasic)),
        .vtable = (struct AllocatorVtable) {
            .alloc = allocator_basic_alloc,
            .realloc = allocator_basic_realloc,
            .free = allocator_basic_free,
        },
    };

    struct AllocatorBasic* allocator_basic = self.handle;
    *allocator_basic = (struct AllocatorBasic) {
        .allocations = 0,
    };

    return self;
}

void
allocator_basic_deinit(
    struct Allocator* self
)
{
    struct AllocatorBasic* allocator_basic = self->handle;
    if (allocator_basic->allocations != 0)
    {
        fprintf(
            stderr,
            "[ERROR][Allocator Basic] Was deinitialized with %zu allocation(s) not "
            "freed.\n",
            allocator_basic->allocations
        );

        abort();
    }

    free(self->handle);

    self = nullptr;
}

#pragma endregion PublicMethods
