cmake_minimum_required(VERSION 3.10)

project(random_vector)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(
    random_vector
    main.cpp
)

set_target_properties(
    random_vector
    PROPERTIES
    OUTPUT_NAME a.out
)

target_include_directories(
    random_vector
    PUBLIC $ENV{PROBLEMS_ROOT_DIR}
)
