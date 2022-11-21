# Mohammed Iyad Benkhaled 
cmake_minimum_required(VERSION 3.24)
project(AvlTree)

set(CMAKE_CXX_STANDARD 20)

include_directories(.)

add_executable(AvlTreeTest
        Test.cpp
        CareUnit.cpp
        ../common/Data.cpp
        ../common/Hospital.cpp
        ../common/Measurement.cpp
        Patient.cpp
        ../common/State.cpp)


# to copy the _data/ folder to the build folder on each build
add_custom_command(
        TARGET AvlTreeTest PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/data
        ${CMAKE_CURRENT_BINARY_DIR}/data)

target_link_libraries(AvlTreeTest)


#cmake_minimum_required(VERSION 3.24)
#project(AVL)
#
#set(CMAKE_CXX_STANDARD 20)
#
#
#
#add_executable(AvlTreeTest
#        Test.cpp
#        CareUnit.cpp
#        CareUnit.hpp
#        Data.cpp
#        Data.hpp
#        dsexceptions.h
#        Hospital.cpp
#        Hospital.hpp
#        Measurement.cpp
#        Measurement.hpp
#        Patient.cpp
#        Patient.hpp
#        State.cpp
#        State.hpp
#        Utils.hpp)
#
#
## to copy the _data/ folder to the build folder on each build
#add_custom_command(
#        TARGET AvlTreeTest PRE_BUILD
#        COMMAND ${CMAKE_COMMAND} -E copy_directory
#        ${CMAKE_SOURCE_DIR}/_data
#        ${CMAKE_CURRENT_BINARY_DIR}/_data)
#
#
#target_link_libraries(AvlTreeTest)