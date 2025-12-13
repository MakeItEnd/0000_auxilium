/**
 * @file allocator.h
 * @author Vele Dan Alexandru (vele.dan.alexandru@gmail.com)
 * @brief Interface and init/deinit method for different type of allocators.
 * @version 0.1
 * @date 2025-10-15
 *
 */

#ifndef HEX_ALLOCATOR_H
#define HEX_ALLOCATOR_H

#include <stddef.h>

struct Allocator;

/**
 * @brief This is the virtual table for all the functions an Allocator MUST implement.
 *
 */
struct AllocatorVtable
{
        void* (*alloc)(
                const struct Allocator* allocator,
                size_t                  size
        );
        void* (*realloc)(
                const struct Allocator* allocator,
                void*                   allocation,
                size_t                  size
        );
        void (*free)(
                const struct Allocator* allocator,
                void*                   allocation
        );
};

struct Allocator
{
        void*                  handle;
        struct AllocatorVtable vtable;
};

void*
allocator_alloc(
        struct Allocator* self,
        size_t            size
);
void*
allocator_realloc(
        struct Allocator* self,
        void*             allocation,
        size_t            size
);
void
allocator_free(
        struct Allocator* self,
        void*             allocation
);

// Allocator Implementations ==================================================
// ============================================================================

// Allocator Basic ------------------------------------------------------------
// ----------------------------------------------------------------------------

#pragma region AllocatorBasic

/**
 * @brief Initialize a basic allocator.
 *
 * @return struct Allocator An instance of basic allocator.
 */
struct Allocator
allocator_basic_init(void);

/**
 * @brief Deinitialize a basic allocator.
 *
 * @param self struct Allocator An instance of a basic allocator.
 */
void
allocator_basic_deinit(struct Allocator* self);

#pragma endregion AllocatorBasic

#endif  // HEX_ALLOCATOR_H
