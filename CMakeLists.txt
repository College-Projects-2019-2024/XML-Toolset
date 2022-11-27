cmake_minimum_required(VERSION 3.23)
project(CollegeProject)

set(CMAKE_CXX_STANDARD 20)

add_executable(CollegeProject main.cpp compression.h compression.cpp Utility.cpp Utility.h hashUtil.cpp hashUtil.h)
