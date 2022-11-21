cmake_minimum_required(VERSION 3.24)
project(CareUnitSystem)

set(CMAKE_CXX_STANDARD 20)

include_directories(common)

add_subdirectory("Hashmap")
add_subdirectory("AVL")
add_subdirectory("BST")

include_directories(common Hashmap)

add_executable(CareUnitSystem
        main.cpp
        Hashmap/CareUnit.cpp
        common/Data.cpp
        common/Hospital.cpp
        common/Measurement.cpp
        Hashmap/Patient.cpp
        common/State.cpp)

