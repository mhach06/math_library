# Matrix Multiplication: Cache & SIMD Optimizations

This module implements and benchmarks three different approaches to standard O(N^3) matrix multiplication. The goal of this project is to demonstrate how physical hardware realities—specifically L1 cache hits and SIMD vectorization—drastically impact execution speeds, even when the algorithmic time complexity remains identical.

## Implementations

1. **Naive (Vertical Access):** 
   The standard nested-loop approach. It iterates horizontally across the first matrix but vertically down the columns of the second matrix. This results in severe cache misses as the CPU constantly stalls waiting for non-contiguous memory from RAM.
   
2. **Cache-Optimized (Horizontal Access):** 
   By swapping the inner loops, the algorithm iterates purely horizontally across both matrices. This guarantees contiguous memory access, allowing the CPU's L1 cache to prefetch data effectively, resulting in an immediate >10x speedup over the naive approach.

3. **SIMD NEON (Vectorized):** 
   Utilizes ARM NEON hardware intrinsics (`arm_neon.h`) to process multiple floating-point numbers simultaneously. 
   * Loads 128-bit chunks (4 floats) at a time using `vld1q_f32`.
   * Broadcasts scalar multipliers across vector lanes using `vdupq_n_f32`.
   * Executes hardware-level Fused Multiply-Add (FMA) operations via `vmlaq_f32` to calculate and accumulate in a single clock cycle.
   * Includes a scalar tail loop to safely handle matrix dimensions that are not perfect multiples of 4.

## Compiler Optimizations (-O0 vs -O3)

The provided `Makefile` includes compiler optimization flags. Testing reveals an interesting dynamic between manual hardware tuning and compiler intelligence:

* **With `-O0` (Optimizations Disabled):** The manual SIMD implementation heavily outperforms the scalar cache-optimized version.
* **With `-O3` (Aggressive Optimizations):** The compiler auto-vectorizes the scalar cache-optimized loop and aggressively unrolls it (processing 16+ floats at once and replacing index math with pointer increments), often allowing the clean scalar code to outpace the strict 4-float manual SIMD implementation.

## Build and Run

A `Makefile` is included to compile the test suite and benchmark the performance in milliseconds and GFLOPS.

```bash
# Compile the object files and link the executable
make

# Run the test suite and performance benchmarks
./test_mult

# Clean up compiled binaries
make clean