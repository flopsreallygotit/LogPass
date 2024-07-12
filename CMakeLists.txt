cmake_minimum_required(VERSION 3.22)
project(log-pass)

set(CMAKE_CXX_STANDARD 14)

find_package(LLVM 14 REQUIRED CONFIG)
find_package(nlohmann_json 3 REQUIRED)

add_definitions(${LLVM_DEFINITIONS})

include_directories(${LLVM_INCLUDE_DIRS})
link_directories(${LLVM_LIBRARY_DIRS})

add_subdirectory(lib)
