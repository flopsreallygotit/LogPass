set(CMAKE_C_COMPILER clang-14)
set(CMAKE_CXX_COMPILER clang++-14)

cmake_minimum_required(VERSION 3.22)
project(log-pass)

set(CMAKE_CXX_STANDARD 23)

find_package(LLVM 14 REQUIRED CONFIG)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)
FetchContent_MakeAvailable(googletest)

add_definitions(${LLVM_DEFINITIONS})

include_directories(${LLVM_INCLUDE_DIRS})
link_directories(${LLVM_LIBRARY_DIRS})

add_subdirectory(lib)
add_subdirectory(src)

enable_testing()
add_subdirectory(tests)
