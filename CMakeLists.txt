cmake_minimum_required(VERSION 3.0)

project(YololTranslatorProject)

include(CTest)
enable_testing(MAKE_DIRECTORY test)

# Dependencies
find_package(Threads REQUIRED)
find_package(nlohmann_json REQUIRED)

# Projects
add_subdirectory(core)
add_subdirectory(discord-bot)
