cmake_minimum_required(VERSION 3.21.2)

target_sources(raytracing PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/matrix.cc
    ${CMAKE_CURRENT_LIST_DIR}/point.cc
    ${CMAKE_CURRENT_LIST_DIR}/vector.cc)
