cmake_minimum_required(VERSION 3.24)
project(HashMap)

set(CMAKE_CXX_STANDARD 20)

include_directories(.)

add_executable(HashMapTest
        Test.cpp
        CareUnit.cpp
        ../common/Data.cpp
        ../common/Hospital.cpp
        ../common/Measurement.cpp
        Patient.cpp
        ../common/State.cpp)


# to copy the _data/ folder to the build folder on each build
add_custom_command(
        TARGET HashMapTest PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/data
        ${CMAKE_CURRENT_BINARY_DIR}/data)

target_link_libraries(HashMapTest)


#cmake_minimum_required(VERSION 3.24)
#project(CareUnitHashmap)
#
#set(CMAKE_CXX_STANDARD 20)
#
#
#
#add_executable(HashMapTest Test.cpp CareUnit.cpp CareUnit.hpp Measurement.cpp Measurement.hpp Patient.cpp Patient.hpp Hospital.cpp Hospital.hpp State.cpp State.hpp Utils.hpp Data.cpp)
#
## to copy the _data/ folder to the build folder on each build
#add_custom_command(
#        TARGET HashMapTest PRE_BUILD
#        COMMAND ${CMAKE_COMMAND} -E copy_directory
#        ${CMAKE_SOURCE_DIR}/_data
#        ${CMAKE_CURRENT_BINARY_DIR}/_data)
#
#target_link_libraries(HashMapTest)