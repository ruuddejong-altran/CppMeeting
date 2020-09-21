project("1. Light")

cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(../../pybind11 ${CMAKE_CURRENT_BINARY_DIR}/pybind11)

add_library(light_lib SHARED light.cpp)

pybind11_add_module(light MODULE light_module.cpp)
target_link_libraries(light PRIVATE light_lib)

add_executable(demo main.cpp)
target_link_libraries(demo light_lib)

add_custom_target(copy_demo ALL
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/demo.py ${CMAKE_CURRENT_BINARY_DIR})
