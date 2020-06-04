cmake_minimum_required(VERSION 3.10)

project(search_in_rotated_array)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(
    search_in_rotated_array
    main.cpp
)

set_target_properties(
    search_in_rotated_array
    PROPERTIES
    OUTPUT_NAME a.out
)

target_include_directories(
    search_in_rotated_array
    PUBLIC $ENV{PROBLEMS_ROOT_DIR}
)
