cmake_minimum_required(VERSION 3.10)

project(sparse_search)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(
    sparse_search
    main.cpp
)

set_target_properties(
    sparse_search
    PROPERTIES
    OUTPUT_NAME a.out
)

target_include_directories(
    sparse_search
    PUBLIC $ENV{PROBLEMS_ROOT_DIR}
)
