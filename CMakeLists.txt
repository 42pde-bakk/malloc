cmake_minimum_required(VERSION 3.17)
project(malloc C)

set(CMAKE_C_STANDARD 11)

file(GLOB srcs "srcs/*.c")
file(GLOB include "include/*.h")

add_library(
        malloc SHARED
        ${srcs}
        ${include}
        main.c
)

include_directories(include)
