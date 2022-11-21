cmake_minimum_required(VERSION 3.24)
project(BinaryTree)

set(CMAKE_CXX_STANDARD 20)

include_directories(.)

add_executable(BinaryTree
        BinarySearchTree.h
        CareUnit.cpp
        CareUnit.hpp
        Data.cpp
        Data.hpp
        dsexceptions.h
        Hospital.cpp
        Hospital.hpp
        main.cpp
        Measurement.cpp
        Measurement.hpp
        Patient.cpp
        Patient.hpp
        State.cpp
        State.hpp
        Utils.hpp)


# to copy the data/ folder to the build folder on each build
add_custom_command(
        TARGET BinaryTree PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/data
        ${CMAKE_CURRENT_BINARY_DIR}/data)

target_link_libraries(BinaryTree)