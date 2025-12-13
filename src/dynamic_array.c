/**
 * @file dynamic_array.c
 * @author Vele Dan Alexandru (vele.dan.alexandru@gmail.com)
 * @brief This file contains the implementation for a dynamic array.
 *
 */

#include "allocator.h"
#include "dynamic_array.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define HEX_DYNAMIC_ARRAY_GROWTH_FACTOR 2
#define HEX_DYNAMIC_ARRAY_INITIAL_CAPACITY 1

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

void*
dynamic_array_init(
        struct Allocator* allocator,
        uint64_t          length,
        uint64_t          stride
)
{
        if (length == 0)
        {
                perror("[ERROR][Dynamic Array] hex_dyanmic_array_init -> Called with `length` of 0.");

                abort();
        }

        uint64_t header_size   = sizeof(DynamicArray_Header);
        uint64_t array_size    = length * stride;
        uint64_t required_size = header_size + array_size;

        // Allocate memory for the new array.
        void* new_array = nullptr;
        new_array       = allocator_alloc(allocator, required_size);

        // ! Failed to allocate array.
        if (new_array == nullptr)
        {
                return nullptr;
        }

        // Initialize the memory block with 0.
        memset(new_array, 0, required_size);

        // Set the header data.
        DynamicArray_Header* header = new_array;
        header->capacity            = length;
        header->length              = 0;
        header->stride              = stride;
        header->allocator           = allocator;

        return (void*)((unsigned char*)new_array + header_size);
}

void
dynamic_array_deinit(
        void* array
)
{
        if (array != nullptr)
        {
                uint64_t             header_size = sizeof(DynamicArray_Header);
                DynamicArray_Header* header      = (DynamicArray_Header*)((unsigned char*)array - header_size);
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
        DynamicArray_Header* header      = (DynamicArray_Header*)((unsigned char*)array - header_size);

        return header->length;
}

void
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
        DynamicArray_Header* header      = (DynamicArray_Header*)((unsigned char*)array - header_size);

        uint64_t addr  = (uint64_t)array;
        addr          += (header->length * header->stride);
        memcpy((void*)addr, value_ptr, header->stride);

        header->length += 1;
}
