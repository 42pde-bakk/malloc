cmake_minimum_required(VERSION 3.17)
project(malloc_tests C)

set(CMAKE_C_STANDARD 11)

include_directories(../include)

add_executable(test_double_free test_double_free.c ../libft_malloc_x86_64_Darwin.so)
add_executable(test_invalid_free test_free_invalid_ptr.c ../libft_malloc_x86_64_Darwin.so)
add_executable(test_allocation test_allocation.c ../libft_malloc_x86_64_Darwin.so)
