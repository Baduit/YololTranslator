cmake_minimum_required(VERSION 3.0)

project(YololTranslatorProjectV2)

add_definitions(-std=c++17 -Wextra -Wall -Wsign-conversion -Wfloat-equal -pedantic -Wredundant-decls -Wshadow -Wpointer-arith -g)

include_directories(hello PRIVATE
      ./external
      ./src
      ./src/Phonem
    )

set(SRCS
	src/main.cpp
	src/Translator.cpp
    src/Phonem/PhonemList.cpp
	src/Phonem/WordsPhonemDictionnary.cpp
    )

add_executable(YololTranslator.exe ${SRCS})