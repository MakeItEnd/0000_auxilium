cmake_minimum_required(VERSION 4.2.0)

PROJECT(AUXILIUM
    VERSION 0.1.0
    DESCRIPTION "A collection of C helpers"
    HOMEPAGE_URL ""
    LANGUAGES C)

add_executable(auxilium)

target_sources(auxilium
    PRIVATE
        "${PROJECT_SOURCE_DIR}/src/main.c"

    PUBLIC
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
    PRIVATE
        "${PROJECT_SOURCE_DIR}/include"
        "${PROJECT_BINARY_DIR}/include")

set_target_properties(auxilium
  PROPERTIES
    C_STANDARD 23
    C_STANDARD_REQUIRED True)

install(TARGETS auxilium DESTINATION bin)

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

