cmake_minimum_required(VERSION 3.10)

project(eight_queens)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(
    eight_queens
    main.cpp
)

set_target_properties(
    eight_queens
    PROPERTIES
    OUTPUT_NAME a.out
)

target_include_directories(
    eight_queens
    PUBLIC $ENV{PROBLEMS_ROOT_DIR}
)
