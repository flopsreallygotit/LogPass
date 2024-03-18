# LogPass

LLVM Pass that logs all IR info and collects code coverage. The project is under development.

## Quick Start

To build pass library write:

```bash
mkdir build
cd build
cmake ..
make
```

Then you can test it on your sources with:

```bash
clang -flegacy-pass-manager -Xclang -load -Xclang build/lib/liblog_pass.so test/test.c
```
