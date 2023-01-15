add_executable(Split.test main.cpp)
target_compile_options(Split.test
                       PRIVATE
                       $<$<CXX_COMPILER_ID:MSVC>:/W3 /permissive- /TP>
                       $<$<CXX_COMPILER_ID:GNU>:-Wextra -Wall -Wsign-conversion -Wfloat-equal -pedantic -Wredundant-decls -Wshadow -Wpointer-arith -g>)
target_link_libraries(Split.test YololTranslator doctest::doctest)
add_test(add Split.test)