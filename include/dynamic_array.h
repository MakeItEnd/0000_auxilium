/**
 * @file dynamic_array.h
 * @author Vele Dan Alexandru (vele.dan.alexandru@gmail.com)
 * @brief This file contains the header definition for a dynamic array.
 * @version 0.1
 * @date 2025-10-16
 *
 */


#ifndef HEX_DYNAMIC_ARRAY_H
#define HEX_DYNAMIC_ARRAY_H


#include "allocator.h"

#include <stdint.h>

// Private functions ----------------------------------------------------------
// ----------------------------------------------------------------------------

// #region Private Methods

void*
_private_dynamic_array_push(
        void* array,
        void* value_ptr
);

void*
_private_dynamic_array_init(
        uint64_t          stride,
        struct Allocator* allocator,
        uint64_t          capacity
);

// #endregion // Private Methods

// Public functions -----------------------------------------------------------
// ----------------------------------------------------------------------------

void*
dynamic_array_init(
        struct Allocator* allocator,
        uint64_t          length,
        uint64_t          stride
);

void
dynamic_array_deinit(void* array);

uint64_t
dynamic_array_length(void* array);


// Public macros --------------------------------------------------------------
// ----------------------------------------------------------------------------

/**
 * @brief Initializez a dynamic array of a given Type.
 *
 * @param Type Used to calculate the stride of the array.
 * @param allocator The allocator used to handel memory for the array.
 * @param capacity The initial capacity to allocate for the array. If a capacity of 0 is passed the HEX_DYNAMIC_ARRAY_INITIAL_CAPACITY will be used.
 *
 * @return A pointer to a newly allocated array of the given Type.
 */
#define dynamic_array_init(Type, allocator, capacity) \
({ \
    (Type*)_private_dynamic_array_init( \
            sizeof(Type),\
            allocator, \
            capacity\
    ); \
})

/**
 * @brief Pushes a new entry to the given array. Resizes if necessary.
 *
 * @param array The array to be pushed to.
 * @param value The value to be pushed. A copy of this value is taken.
 *
 * @returns A pointer to the array block.
 */
#define dynamic_array_push(array, value) \
({ \
    typeof(value) temp = value; \
    array = _private_dynamic_array_push(array, &temp); \
})

#endif  // HEX_DYNAMIC_ARRAY_H
