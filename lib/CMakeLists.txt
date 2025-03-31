add_library(
    dsa_lib 
    STATIC
    src/functor.cpp
    src/quick_uf.cpp
)

target_include_directories(dsa_lib PUBLIC inc)
