set(SRCS
	Translator.cpp
	JsonUnserialiser.cpp
	WordToWord/WordTranslator.cpp
	WordToWord/WordTranslations.cpp
	Phonem/WordToPhonems.cpp
	Phonem/PhonemListToString.cpp
    )

add_library(YololTranslator SHARED ${SRCS} SharedLibInterface.cpp)
target_compile_features(YololTranslator PRIVATE cxx_std_17)
target_compile_options(YololTranslator
                       PRIVATE
                       $<$<CXX_COMPILER_ID:MSVC>:/W3 /permissive- /TP>
					   $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>:-Wextra -Wall -Wsign-conversion -Wfloat-equal -pedantic -Wredundant-decls -Wshadow -Wpointer-arith -O3>)
target_include_directories(YololTranslator PUBLIC ${CMAKE_CURRENT_LIST_DIR})

add_library(StaticYololTranslator STATIC ${SRCS})
target_compile_features(StaticYololTranslator PRIVATE cxx_std_17)
target_compile_options(StaticYololTranslator
                       PRIVATE
                       $<$<CXX_COMPILER_ID:MSVC>:/W3 /permissive- /TP>
					   $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>:-Wextra -Wall -Wsign-conversion -Wfloat-equal -pedantic -Wredundant-decls -Wshadow -Wpointer-arith -O3>)
target_include_directories(StaticYololTranslator PUBLIC ${CMAKE_CURRENT_LIST_DIR})

