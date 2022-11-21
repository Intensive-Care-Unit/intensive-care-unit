cmake_minimum_required(VERSION 3.24)
project(BinaryTree)

set(CMAKE_CXX_STANDARD 20)

include_directories(.)

add_executable(BinaryTreeTest
        Test.cpp
        CareUnit.cpp
        ../common/Data.cpp
        ../common/Hospital.cpp
        ../common/Measurement.cpp
        Patient.cpp
        ../common/State.cpp)


# to copy the _data/ folder to the build folder on each build
add_custom_command(
        TARGET BinaryTreeTest PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/data
        ${CMAKE_CURRENT_BINARY_DIR}/data)

target_link_libraries(BinaryTreeTest)