cmake_minimum_required(VERSION 3.10)

project(single_number)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(
    single_number
    main.cpp
)

set_target_properties(
    single_number
    PROPERTIES
    OUTPUT_NAME a.out
)

target_include_directories(
    single_number
    PUBLIC $ENV{PROBLEMS_ROOT_DIR}
)
