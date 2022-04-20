cmake_minimum_required(VERSION 3.17)
project(malloc C)

set(CMAKE_C_STANDARD 11)


file(GLOB srcs "srcs/*.c")
file(GLOB libc "srcs/libc/*.c")
file(GLOB bonus "srcs/bonus/*.c")
file(GLOB logging "srcs/logging/*.c")
file(GLOB shared "srcs/shared/*.c")
file(GLOB include "include/*.h")

add_library(
        malloc SHARED
        ${srcs}
        ${libc}
        ${shared}
        ${bonus}
        ${logging}
        ${include}
)

include_directories(include)
add_subdirectory(tests)
