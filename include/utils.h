/**
 * @file utils.h
 * @author Vele Dan Alexandru (vele.dan.alexandru@gmail.com)
 * @brief This file contains general utility functions.
 *
 */


#ifndef HEX_UTILS_H
#define HEX_UTILS_H


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
#define MIN(x, y) (x < y ? x : y)

/**
 * @brief Return the Largest of the two given values.
 *
 * @param x The first value to compare.
 * @param y The second value to compare.
 *
 * @returns The largest value.
 */
#define MAX(x, y) (x > y ? x : y)


#endif // HEX_UTILS_H
