cmake_minimum_required(VERSION 3.28)
project(
    dsa
    LANGUAGES 
    C CXX
)

# Enable C++20
set(CMAKE_CXX_STANDARD 20)

# Find the Google Test library (assumes libraries are in /usr/lib)
find_library(GTEST_LIB gtest)
find_library(GTEST_MAIN_LIB gtest_main)

add_subdirectory(libs)

add_executable(
    dsa
    main.cpp
)

target_link_libraries(dsa PRIVATE dsa_libs)