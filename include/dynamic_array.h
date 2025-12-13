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

void
_private_dynamic_array_push(
    void* array,
    void* value_ptr
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
 * @brief Pushes a new entry to the given array. Resizes if necessary.
 *
 * @param array The array to be pushed to.
 * @param value The value to be pushed. A copy of this value is taken.
 *
 * @returns A pointer to the array block.
 */
#define dynamic_array_push(array, value)   \
    {                                          \
        typeof(value) temp = value;            \
        _private_dynamic_array_push(array, &temp); \
    }

#endif  // HEX_DYNAMIC_ARRAY_H
