cmake_minimum_required(VERSION 3.31.1)

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
        "${PROJECT_SOURCE_DIR}/include/utils.h")

target_include_directories(auxilium
    PRIVATE
        "${PROJECT_SOURCE_DIR}/include"
        "${PROJECT_BINARY_DIR}/include")

target_compile_features(auxilium
    PUBLIC
        c_std_23)

install(TARGETS auxilium)
