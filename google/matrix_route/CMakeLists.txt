cmake_minimum_required(VERSION 3.10)

project(matrix_route)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(
    matrix_route
    main.cpp
)

set_target_properties(
    matrix_route
    PROPERTIES
    OUTPUT_NAME a.out
)

target_include_directories(
    matrix_route
    PUBLIC $ENV{PROBLEMS_ROOT_DIR}
)
