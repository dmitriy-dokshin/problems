cmake_minimum_required(VERSION 3.10)

project(rank_from_stream)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(
    rank_from_stream
    main.cpp
)

set_target_properties(
    rank_from_stream
    PROPERTIES
    OUTPUT_NAME a.out
)

target_include_directories(
    rank_from_stream
    PUBLIC $ENV{PROBLEMS_ROOT_DIR}
)
