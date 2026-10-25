# C++ Math Library & Hardware Optimizations

A collection of high-performance mathematical algorithms and linear algebra operations implemented in C++. This repository serves as a workspace for exploring low-level hardware optimizations, memory access patterns, and compiler behavior, specifically targeted at ARM64 architectures.

## Repository Structure

* **`/matrix_multiplication`**: An exploration of cache locality and SIMD vectorization using ARM NEON intrinsics to optimize O(N^3) matrix multiplication.

## Environment & Build Tools
* **Language:** C++17
* **Compiler:** `g++` / `clang++`
* **Target Architecture:** ARM64 / AArch64
* **Build System:** Make

Each sub-module contains its own `Makefile` and benchmarking suite to measure execution time and throughput (GFLOPS). Navigate to individual project folders for specific build instructions and performance analysis.