cmake_minimum_required(VERSION 3.0)

project(YololTranslatorProject)

set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${CMAKE_CURRENT_SOURCE_DIR}/cmake")

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(CMAKE_CXX_STANDARD 20 CACHE STRING "C++ version selection")
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(CPM)
include(CTest)
include(Dependencies)
enable_testing(MAKE_DIRECTORY test)

add_subdirectory(src)
add_subdirectory(bin)

add_subdirectory(test)

pybind11_add_module(yolol src/PythonBindings.cpp)
target_link_libraries(yolol PUBLIC YololTranslator)