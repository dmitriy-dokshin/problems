cmake_minimum_required(VERSION 3.10)

project(common_sorting_algorithms)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(
    common_sorting_algorithms
    main.cpp
)

set_target_properties(
    common_sorting_algorithms
    PROPERTIES
    OUTPUT_NAME a.out
)

target_include_directories(
    common_sorting_algorithms
    PUBLIC $ENV{PROBLEMS_ROOT_DIR}
)
