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
    void** array,
    void*  value_ptr
);

void
_private_dynamic_array_init(
    uint64_t          stride,
    struct Allocator* allocator,
    uint64_t          capacity,
    void**            new_array
);

void
_private_dynamic_array_deinit(void** array);

// #endregion // Private Methods

// Public functions -----------------------------------------------------------
// ----------------------------------------------------------------------------

uint64_t
dynamic_array_length(void const* array);


// Public macros --------------------------------------------------------------
// ----------------------------------------------------------------------------

/**
 * @brief Initializez a dynamic array of a given Type.
 *
 * @param Type Used to calculate the stride of the array.
 * @param allocator The allocator used to handel memory for the array.
 * @param capacity The initial capacity to allocate for the array. If a capacity of 0 is passed the HEX_DYNAMIC_ARRAY_INITIAL_CAPACITY will be used.
 *
 * @return true; The array was initialized succesfully.
 * @return false; The array was NOT initialized succesfully.
 */
#define dynamic_array_init(Type, allocator, capacity, new_array) \
do { \
    _private_dynamic_array_init( \
            sizeof(Type),\
            allocator, \
            capacity,\
            (void**)new_array\
    ); \
} while(0)

/**
 * @brief Pushes a new entry to the given array. Resizes if necessary.
 *
 * @param array The array to be pushed to.
 * @param value The value to be pushed. A copy of this value is taken.
 *
 * @returns A pointer to the array block.
 */
#define dynamic_array_push(array, value) \
do { \
    typeof(value) temp = value; \
    _private_dynamic_array_push((void**)array, &temp); \
} while(0)

/**
 * @brief Deinitialize an allocated array and set to nullptr.
 *
 * @param array The array to deinitialize and set to nullptr.
 */
#define dynamic_array_deinit(array) \
do {\
    _private_dynamic_array_deinit((void**)array); \
} while(0)

#endif  // HEX_DYNAMIC_ARRAY_H
