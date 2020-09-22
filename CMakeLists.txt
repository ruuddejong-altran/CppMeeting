project(airco)

cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

include_directories(src)

add_subdirectory(pybind11 ${CMAKE_CURRENT_BINARY_DIR}/pybind11)

add_library(airco_lib SHARED src/airco.cpp)

pybind11_add_module(airco MODULE src/airco_module.cpp)
target_link_libraries(airco PRIVATE airco_lib)

add_executable(airco_demo src/airco_demo.cpp)
target_link_libraries(airco_demo airco_lib)

add_custom_target(copy_demo ALL
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/src/airco_demo.py ${CMAKE_CURRENT_BINARY_DIR})
