cmake_minimum_required(VERSION 3.24)
project(code)

set(CMAKE_CXX_STANDARD 20)

add_executable(code main.cpp CareUnit.cpp CareUnit.hpp Measurement.cpp Measurement.hpp Patient.cpp Patient.hpp Hospital.cpp Hospital.hpp State.cpp State.hpp Utils.hpp Data.cpp)

add_executable(test Test.cpp CareUnit.cpp CareUnit.hpp Measurement.cpp Measurement.hpp Patient.cpp Patient.hpp Hospital.cpp Hospital.hpp State.cpp State.hpp Utils.hpp Data.cpp)

# to copy the data/ folder to the build folder on each build
add_custom_command(
        TARGET code PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/data
        ${CMAKE_CURRENT_BINARY_DIR}/data)

target_link_libraries(code)
target_link_libraries(test)