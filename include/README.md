A collection of C helpers
=========================

This is a collection of `C` helpers to aid in the development of `C` programs.
This is meant for personal use but anyone is welcome to use anything from here.
Constructive feedback is always welcomed.

> [!CAUTION]
> I an not a professional `C` developer so the code in this repo is most likely not production quality.

# Platform detection

- [platform_detection.h](include/platform_detection.h)

Defined platform specific macros if the code is compiled for said platform, or throws an error for unrecognized platforms.

## Defines:

- `PLATFORM_WINDOWS` :: Is `true` if compiled for the windows platform.
- `PLATFORM_LINUX` :: Is `true` if compiled for the linux platform.
- `PLATFORM_UNIX` :: Is `true` if compiled for the unix platform.
- `PLATFORM_POSIX` :: Is `true` if compiled for the posix platform.
- `PLATFORM_APPLE` :: Is `true` if compiled for the apple platform.
- `PLATFORM_IOS` :: Is `true` if compiled for the ios or ios simulator platform.
- `PLATFORM_IOS_SIMULATOR` :: Is `true` if compiled for the ios simulator platform.

> [!CAUTION]
> Will throw a compile time `#error` if none of the above can be defined.

# General utility functions and macros

- [utils.h](include/utils.h)

## Defines:

- `CLAMP` :: Clamps value to a range of min and max (inclusive).
- `MIN` :: Return the smallest of the two given values.
- `MAX` :: Return the Largest of the two given values.
