/**
 * @file log.h
 * @author Vele Dan Alexandru (vele.dan.alexandru@gmail.com)
 * @brief A logger interface.
 * @version 0.1
 * @date 2025-12-24
 *
 */


#ifndef HEX_LOG_H
#define HEX_LOG_H

/** @brief Represents levels of logging */
typedef enum log_level
{
    /** @brief Fatal log level, should be used to stop the application when hit. */
    LOG_LEVEL_FATAL = 0,
    /** @brief Error log level, should be used to indicate critical runtime problems that cause the application to run improperly or not at all. */
    LOG_LEVEL_ERROR = 1,
    /** @brief Warning log level, should be used to indicate non-critial problems with the application that cause it to run suboptimally. */
    LOG_LEVEL_WARN = 2,
    /** @brief Info log level, should be used for non-erronuous informational purposes. */
    LOG_LEVEL_INFO = 3,
    /** @brief Debug log level, should be used for debugging purposes. */
    LOG_LEVEL_DEBUG = 4,
    /** @brief Trace log level, should be used for verbose debugging purposes. */
    LOG_LEVEL_TRACE = 5
} log_level;

#endif  // HEX_LOG_H
