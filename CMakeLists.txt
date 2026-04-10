cmake_minimum_required(VERSION 4.2.0)

PROJECT(AUXILIUM
    VERSION 0.1.0
    DESCRIPTION "A collection of C helpers"
    HOMEPAGE_URL ""
    LANGUAGES C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# Compiler Warnings
#------------------------------------------------------------------------------
option(AUXILIUM_WARNINGS_AS_ERRORS "Treat warnings as errors"          OFF)
option(AUXILIUM_ENABLE_ASAN        "Enable AddressSanitize"            OFF)
option(AUXILIUM_ENABLE_LSAN        "Enable LeakSanitize"               OFF)
option(AUXILIUM_ENABLE_UBSAN       "Enable UndefinedBehaviourSanitize" OFF)
option(AUXILIUM_ENABLE_TSAN        "Enable ThreadSanitize"             OFF)

add_library(auxilium_sanitizers INTERFACE)

if(AUXILIUM_ENABLE_ASAN)
    target_compile_options(auxilium_sanitizers INTERFACE -fsanitize=address -fno-omit-frame-pointer)
    target_link_options(auxilium_sanitizers    INTERFACE -fsanitize=address)
endif()

if(AUXILIUM_ENABLE_UBSAN)
    target_compile_options(auxilium_sanitizers INTERFACE -fsanitize=undefined)
    target_link_options(auxilium_sanitizers    INTERFACE -fsanitize=undefined)
endif()

if(AUXILIUM_ENABLE_TSAN)
    if(AUXILIUM_ENABLE_ASAN)
        message(FATAL_ERROR "ThreadSanitizer cannot be used together with AddressSanitizer")
    endif()
    target_compile_options(auxilium_sanitizers INTERFACE -fsanitize=thread)
    target_link_options(auxilium_sanitizers    INTERFACE -fsanitize=thread)
endif()


add_library(auxilium_warnings INTERFACE)

if(MSVC)
    target_compile_options(auxilium_warnings INTERFACE
        /W4          # Highest standard warning level.
        /permissive- # Enforce standard conformance.
    )
    if(AUXILIUM_WARNINGS_AS_ERRORS)
        target_compile_options(auxilium_warnings INTERFACE /WX)
    endif()
else()

    target_compile_options(auxilium_warnings INTERFACE
        -Wall              # Common warnings.
        -Wextra            # Extra warnings not covered by -Wall.
        -Wpedantic         # strict ISO C compiliance.
        -Wshadow           # Variable shadows abother in outer scope.
        -Wcast-align       # Potentially misaligned pointer casts.
        -Wcast-qual        # Casts that drop const/volatile qualifiers.
        -Wconversion       # Implicit type conversions that might change value.
        -Wsign-conversion  # Implicit signed/unsigned conversions.
        -Wnull-dereference # Possible null pointer dereference.
        -Wdouble-promotion # Implicit float to double promotion.
        -Wformat=2         # Strict format string checking (printf etc.).
        -Wundef            # Undefined macros used in #if
        -Wwrite-strings    # String literals assigned to non-const pointers.
    )
    if(AUXILIUM_WARNINGS_AS_ERRORS)
        target_compile_options(auxilium_warnings INTERFACE -Werror)
    endif()
endif()

# Main Library
#------------------------------------------------------------------------------
add_library(auxilium INTERFACE)
add_library(auxilium::auxilium ALIAS auxilium)

target_include_directories(auxilium INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>)

# Tests
#------------------------------------------------------------------------------
option(AUXILIUM_BUILD_TESTS "Build tests" ON)

if(AUXILIUM_BUILD_TESTS)
    include(FetchContent)

    FetchContent_Declare(
        unity
        GIT_REPOSITORY https://github.com/ThrowTheSwitch/Unity.git
        GIT_TAG        v2.6.1
        GIT_SHALLOW    TRUE
    )
    FetchContent_MakeAvailable(unity)

    enable_testing()

    # Discover and register all test_*.c files automatically
    file(GLOB TEST_SOURCES tests/test_*.c)

    foreach(TEST_SOURCE ${TEST_SOURCES})
        get_filename_component(TEST_NAME ${TEST_SOURCE} NAME_WE)
        add_executable(${TEST_NAME} ${TEST_SOURCE})
        target_link_libraries(${TEST_NAME} PRIVATE auxilium::auxilium auxilium_warnings auxilium_sanitizers unity)
        add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
    endforeach()
endif()

# Install
# -----------------------------------------------------------------------------
include(GNUInstallDirs)

install(TARGETS auxilium
    EXPORT auxiliumTargets)

install(DIRECTORY include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(EXPORT auxiliumTargets
    FILE auxiliumTargets.cmake
    NAMESPACE auxilium
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/auxilium)
