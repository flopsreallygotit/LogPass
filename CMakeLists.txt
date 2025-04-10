cmake_minimum_required(VERSION 3.22)
project(LogPass)

set(CMAKE_CXX_STANDARD 23)

find_package(LLVM ${LLVM_VERSION} REQUIRED CONFIG)
find_package(Clang ${LLVM_VERSION} REQUIRED)

# Check for Clang compiler
if(NOT CMAKE_C_COMPILER_ID STREQUAL "Clang" OR NOT CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    message(FATAL_ERROR "This project requires Clang for compilation.\n"
        "Detected C compiler: ${CMAKE_C_COMPILER_ID}\n"
        "Detected C++ compiler: ${CMAKE_CXX_COMPILER_ID}")
endif()

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)
FetchContent_MakeAvailable(googletest)

add_definitions(${LLVM_DEFINITIONS})
add_definitions(${CLANG_DEFINITIONS})

include_directories(${LLVM_INCLUDE_DIRS})
include_directories(${CLANG_INCLUDE_DIRS})
link_directories(${LLVM_LIBRARY_DIRS})

add_subdirectory(lib)
add_subdirectory(src)

enable_testing()
add_subdirectory(tests)
