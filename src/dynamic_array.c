/**
 * @file dynamic_array.c
 * @author Vele Dan Alexandru (vele.dan.alexandru@gmail.com)
 * @brief This file contains the implementation for a dynamic array.
 *
 */

#include "dynamic_array.h"

#include "allocator.h"
#include "utils.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define HEX_DYNAMIC_ARRAY_GROWTH_FACTOR 2
#define HEX_DYNAMIC_ARRAY_INITIAL_CAPACITY 16

/** @brief This a dynamic array header. */
typedef struct DynamicArray_Header
{
    /** @brief The length of the array. */
    uint64_t length;
    /** @brief The current allocated capacity of the array. */
    uint64_t capacity;
    /** @brief The stride, sizeof one element of the array */
    uint64_t stride;
    /** @brief A pointer to the memory allocator. */
    void*    allocator;
} DynamicArray_Header;

// Helpers --------------------------------------------------------------------
// ----------------------------------------------------------------------------

/**
 * @brief Resizes an array to the specified capacity.
 *
 * @param array The array to resize.
 * @param capacity The new capacity of the array. If 0 is passed the capacity is increased by a factor of HEX_DYNAMIC_ARRAY_GROWTH_FACTOR.
 *
 * @return A new array with a different capacity
 */
void*
_private_dynamic_array_resize(
    void*    array,
    uint64_t capacity
)
{
    if (array == nullptr)
    {
        perror("[ERROR][Dynamic Array] _private_dynamic_array_resize -> Called on array with nullptr address.\n");

        abort();
    }

    uint64_t             header_size = sizeof(DynamicArray_Header);
    DynamicArray_Header* old_header = (DynamicArray_Header*)((unsigned char*)array - header_size);

    if (capacity == 0)
    {
        capacity = old_header->capacity * HEX_DYNAMIC_ARRAY_GROWTH_FACTOR;
    }

    void* new_array = _private_dynamic_array_init(old_header->stride, old_header->allocator, capacity);
    if (new_array == nullptr)
    {
        // Return the old array if allocation of the new one fails.
        return array;
    }

    DynamicArray_Header* new_header = (DynamicArray_Header*)((unsigned char*)new_array - header_size);
    new_header->length = MIN(old_header->length, new_header->capacity);
    fprintf(stdout, "new_len: %lu\n", new_header->length);
    fprintf(stdout, "new_cap: %lu\n", new_header->capacity);

    memcpy(new_array, array, new_header->length * new_header->stride);

    // TODO: Replace with a LOG
    fprintf(stdout, "[TRACE] I Reallocated!");

    dynamic_array_deinit(array);

    return new_array;
}

void
dynamic_array_deinit(
    void* array
)
{
    if (array != nullptr)
    {
        uint64_t             header_size = sizeof(DynamicArray_Header);
        DynamicArray_Header* header = (DynamicArray_Header*)((unsigned char*)array - header_size);
        // uint64_t total_size =
        //         header_size + header->capacity * header->stride;

        allocator_free(header->allocator, header);
    }
}

uint64_t
dynamic_array_length(
    void* array
)
{
    if (array == nullptr)
    {
        perror("[ERROR][Dynamic Array] dynamic_array_length -> Called on array with nullptr address.\n");

        abort();
    }

    uint64_t             header_size = sizeof(DynamicArray_Header);
    DynamicArray_Header* header = (DynamicArray_Header*)((unsigned char*)array - header_size);

    return header->length;
}

void*
_private_dynamic_array_init(
    uint64_t          stride,
    struct Allocator* allocator,
    uint64_t          capacity
)
{
    if (allocator == nullptr)
    {
        perror("[ERROR][Dynamic Array] hex_dyanmic_array_init -> Called with `allocator` of nullptr.\n");

        abort();
    }

    if (capacity == 0)
    {
        capacity = HEX_DYNAMIC_ARRAY_INITIAL_CAPACITY;
    }

    uint64_t header_size = sizeof(DynamicArray_Header);
    uint64_t array_size = capacity * stride;
    uint64_t required_size = header_size + array_size;

    // Allocate memory for the new array.
    void* new_array = nullptr;
    new_array = allocator_alloc(allocator, required_size);

    // ! Failed to allocate array.
    if (new_array == nullptr)
    {
        return nullptr;
    }

    // Initialize the memory block with 0.
    memset(new_array, 0, required_size);

    // Set the header data.
    DynamicArray_Header* header = new_array;
    header->capacity = capacity;
    header->length = 0;
    header->stride = stride;
    header->allocator = allocator;

    return (void*)((unsigned char*)new_array + header_size);
}

void*
_private_dynamic_array_push(
    void* array,
    void* value_ptr
)
{
    if (array == nullptr)
    {
        perror("[ERROR][Dynamic Array] _dynamic_array_push -> Called on array with nullptr address.\n");

        abort();
    }

    uint64_t             header_size = sizeof(DynamicArray_Header);
    DynamicArray_Header* header = (DynamicArray_Header*)((unsigned char*)array - header_size);
    if (header->length >= header->capacity)
    {
        array = _private_dynamic_array_resize(array, 0);
        header = (DynamicArray_Header*)((unsigned char*)array - header_size);
    }


    uint64_t addr = (uint64_t)array;
    addr += (header->length * header->stride);
    memcpy((void*)addr, value_ptr, header->stride);

    header->length += 1;

    return array;
}
