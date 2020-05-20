cmake_minimum_required(VERSION 3.10)

project(paint_fill)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(
    paint_fill
    main.cpp
)

set_target_properties(
    paint_fill
    PROPERTIES
    OUTPUT_NAME a.out
)
