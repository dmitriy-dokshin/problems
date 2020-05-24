cmake_minimum_required(VERSION 3.10)

project(stack_of_boxes)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(
    stack_of_boxes
    main.cpp
)

set_target_properties(
    stack_of_boxes
    PROPERTIES
    OUTPUT_NAME a.out
)

target_include_directories(
    stack_of_boxes
    PUBLIC $ENV{PROBLEMS_ROOT_DIR}
)
