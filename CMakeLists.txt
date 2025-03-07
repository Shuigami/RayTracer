cmake_minimum_required(VERSION 3.21.2)
project(raytracing)

add_executable(raytracing main.cc)
target_compile_options(raytracing PRIVATE -Wall -Wextra -Werror -std=c++20 -pedantic -Wold-style-cast -g -O0)
target_include_directories(raytracing PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_subdirectory(src)
