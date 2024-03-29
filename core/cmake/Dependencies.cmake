# Dependencies
find_package(Threads REQUIRED)
find_package(nlohmann_json REQUIRED)
find_package(magic_enum CONFIG REQUIRED)
find_package(doctest CONFIG REQUIRED)
#find_package(pybind11 REQUIRED)
#find_package(Python COMPONENTS Interpreter Development)

# CPM Depedencies 
CPMAddPackage(
  NAME thuto
  GITHUB_REPOSITORY  Baduit/Thuto
  #VERSION 0.2.4
  GIT_TAG e39d78cad2434089ff1416d67ebca073ba88e5b5
  OPTIONS "TESTS OFF" "EXAMPLE OFF"
)

CPMAddPackage("gh:pybind/pybind11#v2.10.3")