add_executable(YololTranslatorCli main.cpp)
target_compile_options(YololTranslatorCli
                       PRIVATE
                       $<$<CXX_COMPILER_ID:MSVC>:/W3 /permissive- /TP>
					   $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>:-Wextra -Wall -Wsign-conversion -Wfloat-equal -pedantic -Wredundant-decls -Wshadow -Wpointer-arith -O3>)
target_link_libraries(YololTranslatorCli PRIVATE YololTranslator)
target_include_directories(YololTranslatorCli PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})