cmake_minimum_required(VERSION 3.10)

project(sorted_search_no_size)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(
    sorted_search_no_size
    main.cpp
)

set_target_properties(
    sorted_search_no_size
    PROPERTIES
    OUTPUT_NAME a.out
)

target_include_directories(
    sorted_search_no_size
    PUBLIC $ENV{PROBLEMS_ROOT_DIR}
)
