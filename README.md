# LogPass

LLVM Pass that logs all IR info and collects code coverage. The project is under development.

# Dependencies

You can install dependencies on Debian/Ubuntu with following command:

```bash
sudo apt install clang-14 llvm-14-dev cmake make
```

## Quick Start

To build pass library write:

```bash
mkdir build
cd build
cmake ..
make -j
```

## Usage

Use `loggercc` as C-compiler and `loggercxx` as C++-compiler:

```bash
CC=/path/to/loggercc
CXX=/path/to/loggercxx

cmake / make / ninja / ...
```
