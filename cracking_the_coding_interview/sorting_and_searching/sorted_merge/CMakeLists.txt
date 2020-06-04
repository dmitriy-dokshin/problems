cmake_minimum_required(VERSION 3.10)

project(sorted_merge)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(
    sorted_merge
    main.cpp
)

set_target_properties(
    sorted_merge
    PROPERTIES
    OUTPUT_NAME a.out
)

target_include_directories(
    sorted_merge
    PUBLIC $ENV{PROBLEMS_ROOT_DIR}
)
