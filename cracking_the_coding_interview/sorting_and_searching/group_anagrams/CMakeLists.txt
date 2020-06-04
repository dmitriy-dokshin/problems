cmake_minimum_required(VERSION 3.10)

project(group_anagrams)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(
    group_anagrams
    main.cpp
)

set_target_properties(
    group_anagrams
    PROPERTIES
    OUTPUT_NAME a.out
)

target_include_directories(
    group_anagrams
    PUBLIC $ENV{PROBLEMS_ROOT_DIR}
)
