cmake_minimum_required(VERSION 3.10)

project(count_multiplication_segments)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(
    count_multiplication_segments
    main.cpp
)

set_target_properties(
    count_multiplication_segments
    PROPERTIES
    OUTPUT_NAME a.out
)

target_include_directories(
    count_multiplication_segments
    PUBLIC $ENV{PROBLEMS_ROOT_DIR}
)
