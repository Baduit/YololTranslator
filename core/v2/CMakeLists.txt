cmake_minimum_required(VERSION 3.0)

project(YololTranslatorProjectV2)

add_subdirectory(src)

add_executable(YololTranslatorCmd bin/main.cpp)
target_compile_features(YololTranslatorCmd PRIVATE cxx_std_17)
target_compile_options(YololTranslatorCmd
                       PRIVATE
                       $<$<CXX_COMPILER_ID:MSVC>:/W3 /permissive- /TP>
					   $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>:-Wextra -Wall -Wsign-conversion -Wfloat-equal -pedantic -Wredundant-decls -Wshadow -Wpointer-arith -O3>)
target_link_libraries(YololTranslatorCmd PRIVATE YololTranslator)
target_include_directories(YololTranslatorCmd PRIVATE bin)

include(CTest)
enable_testing(MAKE_DIRECTORY test)
add_subdirectory(test)