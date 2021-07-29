add_executable(YololTranslatorService main.cpp WSService.cpp)
target_compile_features(YololTranslatorService PRIVATE cxx_std_20)
target_compile_options(YololTranslatorService
                       PRIVATE
                       $<$<CXX_COMPILER_ID:MSVC>:/W3 /permissive- /TP>
					   $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>:-Wextra -Wall -Wsign-conversion -Wfloat-equal -pedantic -Wredundant-decls -Wshadow -Wpointer-arith -O3>)
target_link_libraries(YololTranslatorService PRIVATE YololTranslator ZLIB::ZLIB ${USOCKETS_LIB} ${LIBUV_LIB} Threads::Threads nameof::nameof)
target_include_directories(YololTranslatorService PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${UWEBSOCKETS_INCLUDE_DIR})