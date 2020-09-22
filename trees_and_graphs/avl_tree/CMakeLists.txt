cmake_minimum_required(VERSION 3.10)

project(avl_tree)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(
    avl_tree
    main.cpp
)

set_target_properties(
    avl_tree
    PROPERTIES
    OUTPUT_NAME a.out
)

target_include_directories(
    avl_tree
    PUBLIC $ENV{PROBLEMS_ROOT_DIR}
)
