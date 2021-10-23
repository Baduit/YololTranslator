cmake_minimum_required(VERSION 3.0)

project(YololTranslatorProject)

set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include(CPM)
include(CTest)
include(Dependencies)
enable_testing(MAKE_DIRECTORY test)

add_subdirectory(src)
add_subdirectory(bin)

add_subdirectory(test)