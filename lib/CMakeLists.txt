add_library(
    dsa_lib 
    STATIC
    src/functor.cpp
)

target_include_directories(dsa_lib PUBLIC inc)
