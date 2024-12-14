/**
 * @file platform_detection.h
 * @author Vele Dan Alexandru (vele.dan.alexandru@gmail.com)
 * @brief This file contains macro definitions for the corresponding platform the code is being compiled for.
 *
 */


#ifndef HEX_PLATFORM_DETECTION_H
#define HEX_PLATFORM_DETECTION_H


#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
/** @brief Is true if compiled for the windows platform; otherwise is not defined. */
#        define PLATFORM_WINDOWS true
#        ifndef _WIN64
#                error "64-bit is required on Windows!"
#        endif
#elif defined(__linux__) || defined(__gnu_linux__)
/** @brief Is true if compiled for the linux platform; otherwise is not defined. */
#        define PLATFORM_LINUX true
#        if defined(__ANDROID__)
/** @brief Is true if compiled for the android platform; otherwise is not defined. */
#                define PLATFORM_ANDROID true
#        endif
#elif defined(__unix__)
/** @brief Is true if compiled for the unix platform(Catch anything not caught by the above); otherwise is not defined. */
#        define PLATFORM_UNIX true
#elif defined(_POSIX_VERSION)
/** @brief Is true if compiled for the posix platform; otherwise is not defined. */
#        define PLATFORM_POSIX true
#elif __APPLE__
/** @brief Is true if compiled for the apple platform; otherwise is not defined. */
#        define PLATFORM_APPLE true
#        include <TargetConditionals.h>
#        if TARGET_IPHONE_SIMULATOR
/** @brief Is true if compiled for iOS simulator platform; otherwise is not defined. */
#                define PLATFORM_IOS           true
#                define PLATFORM_IOS_SIMULATOR true
#        elif TARGET_OS_IPHONE
/** @brief Is true if compiled for the iOS device; otherwise is not defined. */
#                define PLATFORM_IOS true
#        elif TARGET_OS_MAC
// Other kinds of MacOs (Do nothing for now) ----------------------------------
#        else
// Other kinds of Mac OS ------------------------------------------------------
#                error "Unknown Apple platform"
#        endif
#else
// Unknown platform -----------------------------------------------------------
#        error "Unknown platform!"
#endif


#endif // HEX_PLATFORM_DETECTION_H
