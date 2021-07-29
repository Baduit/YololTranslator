# Dependencies
find_package(Threads REQUIRED)
find_package(nlohmann_json REQUIRED)
find_package(magic_enum CONFIG REQUIRED)
find_package(doctest CONFIG REQUIRED)
find_package(nameof REQUIRED)

find_package(ZLIB REQUIRED)
find_library(USOCKETS_LIB uSockets)
find_package(unofficial-libuv CONFIG REQUIRED)
find_library(LIBUV_LIB libuv)
find_path(UWEBSOCKETS_INCLUDE_DIR uwebsockets)

# CPM Depedencies 
CPMAddPackage(
  NAME thuto
  GITHUB_REPOSITORY  Baduit/Thuto
  #VERSION 0.2.4
  GIT_TAG ef32356db9ca09299ef12b3895b547b9d1ca078d
  OPTIONS "TESTS OFF" "EXAMPLE OFF"
)