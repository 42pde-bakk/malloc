cmake_minimum_required(VERSION 3.17)
project(malloc C)

set(CMAKE_C_STANDARD 11)

add_library(malloc SHARED srcs/malloc.c srcs/free.c srcs/realloc.c include/peer_stdlib.h main.c)

include_directories(include)
