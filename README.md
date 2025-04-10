# LogPass

LogPass provides compiler wrapper and pass library that logs function traces

# Dependencies

You can install dependencies on Debian/Ubuntu with following command:

```bash
sudo apt install clang-16 llvm-16-dev cmake make
```

## Quick Start

To build pass library write:

```bash
mkdir build
cd build
cmake .. -DCMAKE_C_COMPILER=clang-16 -DCMAKE_CXX_COMPILER=clang++-16
make -j
```

## Usage

Use `loggercc` as C-compiler and `loggercxx` as C++-compiler:

```bash
CC=/path/to/loggercc
CXX=/path/to/loggercxx

cmake / make / ninja / ...
./a.out
```

You'll receive `logger.log` file with function trace.
