cmake_minimum_required(VERSION 3.0)

project(hello)

set (CMAKE_CXX_FLAGS "--std=gnu++14")

set(SRCS
    src/main.cpp
    )

add_executable(YololTranslator.exe ${SRCS})