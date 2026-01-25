/**
 * @file utils.h
 * @author Vele Dan Alexandru (vele.dan.alexandru@gmail.com)
 * @brief This file contains general utility functions.
 *
 */


#ifndef HEX_UTILS_H
#define HEX_UTILS_H

/**
 * @brief Returns the amount of bytes in n Kibibytes.
 *
 * @param n The amount of Kibibytes.
 *
 * @return The amount of bytes in n Kibibytes.
 */
#define KiB(n) ((uint64_t)(n) << 10)

/**
 * @brief Returns the amount of bytes in n Mibibytes.
 *
 * @param n The amount of Mibibytes.
 *
 * @return The amount of bytes in n Mibibytes.
 */
#define MiB(n) ((uint64_t)(n) << 20)

/**
 * @brief Returns the amount of bytes in n Gibibytes.
 *
 * @param n The amount of Gibibytes.
 *
 * @return The amount of bytes in n Gibibytes.
 */
#define GiB(n) ((uint64_t)(n) << 30)

#define ALIGN_UP_POW2(n, p) (((uint64_t)(n) + ((uint64_t)(p) - 1)) & (~((uint64_t)(p) - 1)))

/**
 * @brief Clamps value to a range of min and max (inclusive).
 *
 * @param value The value to be clamped.
 * @param min The minimum value of the range.
 * @param max The maximum value of the range.
 *
 * @returns The clamped value.
 */
#define CLAMP(value, min, max) ((value <= min) ? min : (value >= max) ? max : value)

/**
 * @brief Return the smallest of the two given values.
 *
 * @param x The first value to compare.
 * @param y The second value to compare.
 *
 * @returns The smallest value.
 */
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

/**
 * @brief Return the Largest of the two given values.
 *
 * @param x The first value to compare.
 * @param y The second value to compare.
 *
 * @returns The largest value.
 */
#define MAX(x, y) (((x) > (y)) ? (x) : (y))


#endif // HEX_UTILS_H
