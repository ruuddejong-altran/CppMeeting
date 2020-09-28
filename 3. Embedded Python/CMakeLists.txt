cmake_minimum_required(VERSION 3.15)
project(embedded)


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

include_directories(src)

add_subdirectory(../pybind11 ${CMAKE_CURRENT_BINARY_DIR}//pybind11)

add_library(airco_lib SHARED
        src/airco.cpp
        src/cooler.cpp
        src/controller.cpp
        src/room.cpp
        )

pybind11_add_module(airco MODULE src/airco_module.cpp)
target_link_libraries(airco PRIVATE airco_lib)

add_executable(cooler_demo src/cooler_demo.cpp)
target_link_libraries(cooler_demo PRIVATE airco_lib)

add_executable(controller_demo src/controller_demo.cpp)
target_link_libraries(controller_demo PRIVATE airco_lib)

add_executable(airco_demo src/airco_demo.cpp)
target_link_libraries(airco_demo PRIVATE airco_lib pybind11::embed)

add_executable(room_demo src/room_demo.cpp)
target_link_libraries(room_demo PRIVATE airco_lib)

add_custom_target(copy_demo ALL
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/src/airco_demo.py ${CMAKE_CURRENT_BINARY_DIR})
