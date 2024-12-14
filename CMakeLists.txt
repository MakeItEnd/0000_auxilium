cmake_minimum_required(VERSION 3.31.1)

PROJECT(AUXILIUM
    VERSION 0.1.0
    DESCRIPTION "A collection of C helpers"
    HOMEPAGE_URL ""
    LANGUAGES C)

add_executable(auxilium
    "src/main.c")

target_include_directories(auxilium
    PRIVATE
        "${PROJECT_SRC_ROOT}/include")

target_compile_features(auxilium
    PUBLIC
        c_std_23)

install(TARGETS auxilium)
