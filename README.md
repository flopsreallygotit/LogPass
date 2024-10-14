# LogPass

LLVM Pass that logs all IR info and collects code coverage. The project is under development.

# Dependencies

You can install dependencies on Debian/Ubuntu with following command:

```bash
sudo apt install nlohmann-json3-dev clang-14 llvm-14-dev cmake make
```

## Quick Start

To build pass library write:

```bash
mkdir build
cd build
cmake ..
make
```

## Usage

Then you can test it on your sources with:

```bash
clang -fpass-plugin=build/lib/liblog_pass.so -lstdc++ test.c
clang++ -fpass-plugin=build/lib/liblog_pass.so test.cpp
```

For big projects use following flags:

```bash
export CFLAGS="-g -O0 -fpass-plugin=/path/to/liblog_pass.so"
export CXXFLAGS="-g -O0 -fpass-plugin=/path/to/liblog_pass.so"
export LDFLAGS="-lstdc++"
```
