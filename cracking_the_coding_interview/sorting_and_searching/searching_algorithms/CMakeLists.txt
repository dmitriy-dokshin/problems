cmake_minimum_required(VERSION 3.10)

project(searching_algorithms)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(
    searching_algorithms
    main.cpp
)

set_target_properties(
    searching_algorithms
    PROPERTIES
    OUTPUT_NAME a.out
)

target_include_directories(
    searching_algorithms
    PUBLIC $ENV{PROBLEMS_ROOT_DIR}
)
