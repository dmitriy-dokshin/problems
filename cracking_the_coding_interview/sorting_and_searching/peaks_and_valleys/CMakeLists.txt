cmake_minimum_required(VERSION 3.10)

project(peaks_and_valleys)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(
    peaks_and_valleys
    main.cpp
)

set_target_properties(
    peaks_and_valleys
    PROPERTIES
    OUTPUT_NAME a.out
)

target_include_directories(
    peaks_and_valleys
    PUBLIC $ENV{PROBLEMS_ROOT_DIR}
)
