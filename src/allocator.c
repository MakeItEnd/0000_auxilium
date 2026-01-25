/**
 * @file allocator.c
 * @author Vele Dan Alexandru (vele.dan.alexandru@gmail.com)
 * @brief The common interface functions implemented by all allocators.
 * @version 0.1
 * @date 2025-10-16
 *
 */

#include "allocator.h"

void*
allocator_alloc(
    struct Allocator* self,
    size_t            size
)
{
    return self->vtable.alloc(self, size);
}

void*
allocator_realloc(
    struct Allocator* self,
    void*             allocation,
    size_t            size
)
{
    return self->vtable.realloc(self, allocation, size);
}

void
allocator_free(
    struct Allocator* self,
    void*             allocation
)
{
    self->vtable.free(self, allocation);
}
