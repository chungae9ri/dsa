cmake_minimum_required(VERSION 3.28)
project(
    dsa
    LANGUAGES 
    C CXX
)

# Enable C++20
set(CMAKE_CXX_STANDARD 20)

# Find the Google Test library (assumes libraries are in /usr/lib)
find_package(GTest REQUIRED)

add_executable(
    dsa_test
    main_test.cpp
)

target_link_libraries(
    dsa_test
    PRIVATE 
    GTest::GTest 
    pthread
    dsa_lib
)
