cmake_minimum_required(VERSION 3.23)
add_link_options(-pthread)
set(CMAKE_CXX_STANDARD 23)

project(solver)
add_executable(solver src/main.cpp)
add_subdirectory(src)

find_package(fmt CONFIG REQUIRED)
target_link_libraries(solver PRIVATE fmt::fmt-header-only)

target_link_libraries(solver PRIVATE d3d9)
target_link_libraries(solver PRIVATE dwmapi)