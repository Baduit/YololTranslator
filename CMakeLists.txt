cmake_minimum_required(VERSION 3.0)

project(YololTranslatorProject)

set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include(CPM)
include(CTest)
enable_testing(MAKE_DIRECTORY test)

# Dependencies
find_package(Threads REQUIRED)
find_package(nlohmann_json REQUIRED)
find_package(magic_enum CONFIG REQUIRED)
find_package(doctest CONFIG REQUIRED)
find_package(cpr CONFIG REQUIRED)

#find_package(mbedTLS REQUIRED)
find_library(MBEDTLS_TLS_LIBRARY mbedtls)
find_library(MBEDTLS_X509_LIBRARY mbedx509)
find_library(MBEDTLS_CRYPTO_LIBRARY mbedcrypto)

find_path(IXWEBSOCKET_INCLUDE_DIR ixwebsocket/IXWebSocket.h)
find_library(IXWEBSOCKET_LIBRARY ixwebsocket)

# CPM Depedencies 
CPMAddPackage(
  NAME thuto
  GITHUB_REPOSITORY  Baduit/Thuto
  #VERSION 0.2.4
  GIT_TAG ef32356db9ca09299ef12b3895b547b9d1ca078d
  OPTIONS "TESTS OFF" "EXAMPLE OFF"
)

CPMAddPackage(
  NAME discord_cpp
  GITHUB_REPOSITORY  luccanunes/discord.cpp
  GIT_TAG afdd7fc4f7ed4af880d72b8a69b13a3b9a7ddf5a
  DOWNLOAD_ONLY True
)
if (discord_cpp_ADDED)
  # Create the library (I don't use directly the CMakeList.txt because it fetch the dependencies but I use vcpkg instead)
  add_library(discord_cpp
    "${discord_cpp_SOURCE_DIR}/src/Api.cpp"
    "${discord_cpp_SOURCE_DIR}/src/Channel.cpp"
    "${discord_cpp_SOURCE_DIR}/src/Client.cpp"
    "${discord_cpp_SOURCE_DIR}/src/Command.cpp"
    "${discord_cpp_SOURCE_DIR}/src/Embed.cpp"
    "${discord_cpp_SOURCE_DIR}/src/Guild.cpp"
    "${discord_cpp_SOURCE_DIR}/src/Message.cpp"
    "${discord_cpp_SOURCE_DIR}/src/Role.cpp"
    "${discord_cpp_SOURCE_DIR}/src/urlEncode.cpp"
    "${discord_cpp_SOURCE_DIR}/src/User.cpp"
    "${discord_cpp_SOURCE_DIR}/src/Webhook.cpp"
    )

  target_link_libraries(discord_cpp PRIVATE cpr nlohmann_json::nlohmann_json ${IXWEBSOCKET_LIBRARY} ${MBEDTLS_TLS_LIBRARY} ${MBEDTLS_X509_LIBRARY} ${MBEDTLS_CRYPTO_LIBRARY})
  target_include_directories(discord_cpp PUBLIC "${discord_cpp_SOURCE_DIR}/src" ${IXWEBSOCKET_INCLUDE_DIR})
endif()

# Projects
add_subdirectory(core)
add_subdirectory(discord-bot)
