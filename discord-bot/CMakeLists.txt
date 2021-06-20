add_executable(DiscordBot src/main.cpp)
target_compile_features(DiscordBot PRIVATE cxx_std_20)
target_compile_options(DiscordBot
                       PRIVATE
                       $<$<CXX_COMPILER_ID:MSVC>:/W3 /permissive- /TP>
					   $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>:-Wextra -Wall -Wsign-conversion -Wfloat-equal -pedantic -Wredundant-decls -Wshadow -Wpointer-arith -O3>)
target_link_libraries(DiscordBot PRIVATE Threads::Threads discord_cpp)
target_include_directories(DiscordBot PRIVATE src)