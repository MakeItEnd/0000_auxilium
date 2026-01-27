cmake_minimum_required(VERSION 4.2.0)

PROJECT(AUXILIUM
    VERSION 0.1.0
    DESCRIPTION "A collection of C helpers"
    HOMEPAGE_URL ""
    LANGUAGES C)

add_library(auxilium)

target_sources(auxilium
    PUBLIC
        "${PROJECT_SOURCE_DIR}/include/auxilium.h"

    PRIVATE
        "${PROJECT_SOURCE_DIR}/include/platform_detection.h"
        "${PROJECT_SOURCE_DIR}/include/utils.h"

        # Allocators
        "${PROJECT_SOURCE_DIR}/include/allocator.h"
        "${PROJECT_SOURCE_DIR}/src/allocator.c"
        "${PROJECT_SOURCE_DIR}/src/allocators/allocator_basic.c"

        # Dynamic array
        "${PROJECT_SOURCE_DIR}/include/dynamic_array.h"
        "${PROJECT_SOURCE_DIR}/src/dynamic_array.c")

target_include_directories(auxilium
    PUBLIC
        "${PROJECT_SOURCE_DIR}/include"
        "${PROJECT_BINARY_DIR}/include")

set_target_properties(auxilium
  PROPERTIES
    C_STANDARD 23
    C_STANDARD_REQUIRED ON
    C_EXTENSIONS OFF)


if(MSVC)
  target_compile_options(auxilium PRIVATE /W4 /WX)
else()
  target_compile_options(auxilium PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()

install(TARGETS auxilium DESTINATION bin)


add_executable(auxilium_tests)
target_sources(auxilium_tests PRIVATE "${PROJECT_SOURCE_DIR}/examples/main.c")
target_link_libraries(auxilium_tests PRIVATE auxilium)

# target_compile_options(auxilium_tests
#   PRIVATE
#     -fno-omit-frame-pointer
#     -fsanitize=address)
# set (CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")
# set (CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_LINKER_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")
if(CMAKE_BUILD_TYPE MATCHES "Debug")
  set(
    CMAKE_C_FLAGS
    "${CMAKE_C_FLAGS} -Werror -fsanitize=undefined -fsanitize=address"
  )
  target_link_options(auxilium_tests
    BEFORE PUBLIC -fsanitize=undefined PUBLIC -fsanitize=address
  )
endif()

set_target_properties(auxilium_tests
  PROPERTIES
    C_STANDARD 23
    C_STANDARD_REQUIRED ON
    C_EXTENSIONS OFF)
# target_include_directories(auxilium_tests PRIVATE ${auxilium_INCLUDE_DIRS})

# enable_testing()

# function(do_test target exercise exercise_input result)
#   add_test(NAME Exercise${exercise}${exercise_input} COMMAND ${target} ${exercise} ${exercise_input})
#   set_tests_properties(Exercise${exercise}${exercise_input}
#     PROPERTIES PASS_REGULAR_EXPRESSION ${result}
#     )
# endfunction()

# do_test(aoc 2015_01 "(())" 0)
# do_test(aoc 2015_01 "()()" 0)
# do_test(aoc 2015_01 "(((" 3)
# do_test(aoc 2015_01 "(()(()(" 3)
# do_test(aoc 2015_01 "))(((((" 3)
# do_test(aoc 2015_01 "())" -1)
# do_test(aoc 2015_01 "))(" -1)
# do_test(aoc 2015_01 ")))" -3)
# do_test(aoc 2015_01 ")())())" -3)

