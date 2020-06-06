cmake_minimum_required(VERSION 3.10)

project(find_duplicates)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(
    find_duplicates
    main.cpp
)

set_target_properties(
    find_duplicates
    PROPERTIES
    OUTPUT_NAME a.out
)

target_include_directories(
    find_duplicates
    PUBLIC $ENV{PROBLEMS_ROOT_DIR}
)
