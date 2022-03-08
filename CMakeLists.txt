cmake_minimum_required(VERSION 3.0.0)
project(imgui_test VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(imgui_test init.cpp)

set (CMAKE_CXX_STANDARD 20)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
set(CMAKE_GENERATOR_PLATFORM x64)
include(CPack)
