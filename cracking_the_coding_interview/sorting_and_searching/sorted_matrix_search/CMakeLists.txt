cmake_minimum_required(VERSION 3.10)

project(sorted_matrix_search)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(
    sorted_matrix_search
    main.cpp
)

set_target_properties(
    sorted_matrix_search
    PROPERTIES
    OUTPUT_NAME a.out
)

target_include_directories(
    sorted_matrix_search
    PUBLIC $ENV{PROBLEMS_ROOT_DIR}
)
