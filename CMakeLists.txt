cmake_minimum_required(VERSION 3.24)
project(code)

set(CMAKE_CXX_STANDARD 20)

add_executable(code main.cpp CareUnit.cpp CareUnit.hpp Measurement.cpp Measurement.hpp Patient.cpp Patient.hpp Hospital.cpp Hospital.hpp)
