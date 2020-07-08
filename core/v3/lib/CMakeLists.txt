set(SRCS
    Translator.cpp
  )

add_library(YololTranslator STATIC ${SRCS})
target_compile_features(YololTranslator PRIVATE cxx_std_17)
target_compile_options(YololTranslator
                       PRIVATE
                       $<$<CXX_COMPILER_ID:MSVC>:/W3 /permissive- /TP>
                       $<$<CXX_COMPILER_ID:GNU>:-Wextra -Wall -Wsign-conversion -Wfloat-equal -pedantic -Wredundant-decls -Wshadow -Wpointer-arith -g -O3>)
target_include_directories(YololTranslator
                           PUBLIC
                           ${CMAKE_CURRENT_LIST_DIR})

# Add sharedlibrary ???