cmake_minimum_required(VERSION 3.23)
set(CMAKE_CXX_STANDARD 23)

project(solver)
add_executable(solver src/main.cpp)
add_subdirectory(src)