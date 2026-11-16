# C++ Fourier Transform Library

A high-performance C++ mathematics library exploring the Fourier Transform. 

The goal of this project is to build an optimized Fast Fourier Transform (FFT) capable of competing with GCC's `-O3` compiler optimizations. The project is currently in its foundational phase.

## Current State: Baseline DFT
Currently, the library implements the **Discrete Fourier Transform (DFT)** in standard $O(N^2)$ time. This serves as the mathematical baseline to guarantee the correctness of future $O(N \log N)$ FFT implementations.

The baseline computes the frequency domain translation using Euler's formula ($e^{-j\theta} = \cos(\theta) - j\sin(\theta)$):
$$X_k = \sum_{n=0}^{N-1} x_n \cdot (\cos(\theta) - j\sin(\theta))$$

### Features
* **In-Place Execution:** Safe memory handling to prevent state corruption during time-to-frequency mapping.
* **Complex Number Integration:** Native handling of `std::complex<double>` for I/Q signals.
* **Test & Benchmarking Suite:** An expandable `main.cpp` harness that verifies algorithm correctness against known impulse/DC signals and provides microsecond-precision performance benchmarking.

## Build Instructions
This project requires a compiler that supports C++20 (for `<numbers>`). 

To compile the test bench with maximum optimizations (`-O3` and `-march=native`):
```bash
make