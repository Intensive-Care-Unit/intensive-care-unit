cmake_minimum_required(VERSION 3.24)
project(CareUnitSystem)

set(CMAKE_CXX_STANDARD 20)

include_directories(common)

add_subdirectory("Hashmap")
add_subdirectory("AVL")
add_subdirectory("BST")

include_directories(Hashmap Driver include)

add_executable(CareUnitSystem
        main.cpp
        Hashmap/CareUnit.cpp
        common/Data.cpp
        common/Hospital.cpp
        common/Measurement.cpp
        Hashmap/Patient.cpp
        common/State.cpp)


# to copy the _data/ folder to the build folder on each build
add_custom_command(
        TARGET CareUnitSystem PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/data
        ${CMAKE_CURRENT_BINARY_DIR}/data)

target_link_libraries(CareUnitSystem)