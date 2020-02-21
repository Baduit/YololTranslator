cmake_minimum_required(VERSION 3.9)

project(YololV3 VERSION 0.1 DESCRIPTION "YololTranslator 3rd version.")

set(SRCS
    ${CMAKE_CURRENT_LIST_DIR}/src/main.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/Translator.cpp
  )


add_executable(YololTranslator ${SRCS})

target_compile_features(YololTranslator PRIVATE cxx_std_17)

target_compile_options(YololTranslator
                       PRIVATE
                       $<$<CXX_COMPILER_ID:MSVC>:/W3 /permissive- /TP>
                       $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>:-Wextra -Wall -Wsign-conversion -Wfloat-equal -pedantic -Wredundant-decls -Wshadow -Wpointer-arith -O3>)

target_include_directories(YololTranslator
                           PUBLIC
                           ${CMAKE_CURRENT_LIST_DIR}/src)

