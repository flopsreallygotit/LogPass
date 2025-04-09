FROM ubuntu:latest as LogPass

WORKDIR /LogPass
COPY . .

RUN apt-get update && \
    apt-get install -y && \
    clang-14 llvm-14 cmake make && \
    rm -rf /var/lib/apt/lists/*

RUN apt clean -y

RUN mkdir build && \
    cd build && \
    cmake ..

RUN cd build && make -j
