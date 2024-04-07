cmake_minimum_required(VERSION 3.20)
project(nooblink)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE Debug)

enable_testing()
add_subdirectory(src)