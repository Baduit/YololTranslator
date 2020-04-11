cmake_minimum_required(VERSION 3.12)

project(YololTranslatorCinematicUniverse VERSION 0.1 DESCRIPTION "YololTranslator 3rd episode")

add_subdirectory(lib)

add_executable(YololTranslatorCmd ./bin/main.cpp)
target_compile_features(YololTranslatorCmd PRIVATE cxx_std_17)
target_compile_options(YololTranslatorCmd
                       PRIVATE
                       $<$<CXX_COMPILER_ID:MSVC>:/W3 /permissive- /TP>
                       $<$<CXX_COMPILER_ID:GNU>:-Wextra -Wall -Wsign-conversion -Wfloat-equal -pedantic -Wredundant-decls -Wshadow -Wpointer-arith -g>)

target_link_libraries(YololTranslatorCmd PRIVATE YololTranslator)