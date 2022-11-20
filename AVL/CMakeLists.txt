cmake_minimum_required(VERSION 3.24)
project(AVL)

set(CMAKE_CXX_STANDARD 20)

include_directories(.)

# Enable debug symbols by default
#if (NOT CMAKE_BUILD_TYPE)
#    set(CMAKE_BUILD_TYPE Release
#            CACHE STRING
#            "Choose the type of build (Debug or Release)" FORCE)
#endif ()

#set(CMAKE_CXX_FLAGS "-J9 -O3")

add_executable(AvlTree
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

add_executable(AvlTreeTest
        Test.cpp
        CareUnit.cpp
        CareUnit.hpp
        Data.cpp
        Data.hpp
        dsexceptions.h
        Hospital.cpp
        Hospital.hpp
        Measurement.cpp
        Measurement.hpp
        Patient.cpp
        Patient.hpp
        State.cpp
        State.hpp
        Utils.hpp)


# to copy the data/ folder to the build folder on each build
add_custom_command(
        TARGET AvlTree PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/data
        ${CMAKE_CURRENT_BINARY_DIR}/data)


target_link_libraries(AvlTree)
target_link_libraries(AvlTreeTest)