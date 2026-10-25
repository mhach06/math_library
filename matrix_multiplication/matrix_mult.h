#ifndef MATRIX_MULT_H
#define MATRIX_MULT_H

#include <vector>

// Helper utility for 1D indexing
inline int get_idx(int row, int col, int size) {
    return row * size + col;
}

// Function declarations
void matrix_multiplication_naive(
    const std::vector<float>& m1, 
    const std::vector<float>& m2,
    std::vector<float>& result,
    int size);

void matrix_multiplication_cache(
    const std::vector<float>& m1, 
    const std::vector<float>& m2,
    std::vector<float>& result,
    int size);

void matrix_multiplication_simd(
    const std::vector<float>& m1, 
    const std::vector<float>& m2,
    std::vector<float>& result,
    int size);

#endif 