cmake_minimum_required(VERSION 3.10)

project(search_big_file)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(
    search_big_file
    main.cpp
)

set_target_properties(
    search_big_file
    PROPERTIES
    OUTPUT_NAME a.out
)

target_include_directories(
    search_big_file
    PUBLIC $ENV{PROBLEMS_ROOT_DIR}
)
