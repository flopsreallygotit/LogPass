cmake_minimum_required(VERSION 3.22)
project(log-pass)

set(CMAKE_CXX_STANDARD 14)

find_package(LLVM REQUIRED CONFIG) # TODO add exact llvm version, bc. of unstable llvm's interface

add_definitions(${LLVM_DEFINITIONS})
include_directories(${LLVM_INCLUDE_DIRS})
link_directories(${LLVM_LIBRARY_DIRS})

add_subdirectory(lib)
