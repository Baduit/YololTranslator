add_executable(Translator.test main.cpp)
target_compile_options(Translator.test
                       PRIVATE
                       $<$<CXX_COMPILER_ID:MSVC>:/W3 /permissive- /TP>
                       $<$<CXX_COMPILER_ID:GNU>:-Wextra -Wall -Wsign-conversion -Wfloat-equal -pedantic -Wredundant-decls -Wshadow -Wpointer-arith -g>)
target_link_libraries(Translator.test YololTranslator doctest::doctest)
add_test(add Translator.test)