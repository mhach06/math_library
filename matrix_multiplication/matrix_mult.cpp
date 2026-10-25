#include "matrix_mult.h"
#include <arm_neon.h> // ARM NEON intrinsics


// Original Naive (Vertical) - O(N^3) with severe cache misses
void matrix_multiplication_naive(
    const std::vector<float>& m1, 
    const std::vector<float>& m2,
    std::vector<float>& result,
    int size) 
{
    for (int outer_row = 0; outer_row < size; outer_row++) {
        for (int outer_col = 0; outer_col < size; outer_col++) {
            float cur_dot_product = 0;
            for (int cur = 0; cur < size; cur++) {
                float m1_num = m1[get_idx(outer_row, cur, size)];
                float m2_num = m2[get_idx(cur, outer_col, size)];
                cur_dot_product += (m1_num * m2_num);
            }
            result[get_idx(outer_row, outer_col, size)] = cur_dot_product;
        }
    }
}

// Cache-Optimized (Horizontal) - O(N^3) but memory contiguous
void matrix_multiplication_cache(
    const std::vector<float>& m1, 
    const std::vector<float>& m2,
    std::vector<float>& result,
    int size) 
{
    /*
    assume m1 col number is 0 (first one), then it's multiplied by all nums
    in row 0 in m2. if col number is 1 (Second col), then row 2 in m2. 

    cpu caches contiguous memory in l1 cache, since using flattened vector, rows are 
    stored one after the other. instead of jumping to next row in same col 
    (high number of bytes, cpu must wait until RAM loads it from hard drive, takes too long),
    simply loop through rows themselves, computing each individual multiplication and summing each
    linear combination separately, eventually summing what would have been the regular dot product.

    essentially same number of computations, except accessing memory in a more efficient way.
    */
    
    for (int outer_row = 0; outer_row < size; outer_row++) {
        // loops through m1 row, single num to multiply by full row in m2
        for (int outer_col = 0; outer_col < size; outer_col++) {
            float m1_num = m1[get_idx(outer_row, outer_col, size)];
            // loops through m2 row nums
            for (int inner_col = 0; inner_col < size; inner_col++) {
                float m2_num = m2[get_idx(outer_col, inner_col, size)];
                
                // add this specific multiplication to the large linear combination which will eventually be 
                // regular dot product.
                result[get_idx(outer_row, inner_col, size)] += m1_num * m2_num; 
            }

        }
    }
}

// SIMD-Optimized (Horizontal + Vectorized) - M2 NEON Intrinsics
void matrix_multiplication_simd(
    const std::vector<float>& m1, 
    const std::vector<float>& m2,
    std::vector<float>& result,
    int size) 
{
    /*
    quick note: vld1q means loading 4 floats. vld1 is 2 floats. want to use 128-bit register in this code.
    */
    for (int outer_row = 0; outer_row < size; outer_row++) {
        for (int outer_col = 0; outer_col < size; outer_col++) {
            // m1 num in col m which will multiply all nums in row m
            float32_t m1_num = m1[get_idx(outer_row, outer_col, size)];
            float32x4_t m1_num_vector = vdupq_n_f32(m1_num);
            
            int inner_col = 0; // used to ensure we don't have leftovers
            for (; inner_col <= size - 4; inner_col += 4) {
                float32x4_t m2_nums_vector = vld1q_f32(&m2[get_idx(outer_col, inner_col, size)]);
                
                float32x4_t cur_result_vec = vld1q_f32(&result[get_idx(outer_row, inner_col, size)]);
                
                // vmlaq takes a, b, c. vmlaq does a[i] + (b[i] * c[i]).
                // does multiply then add to result (replaces previous nested vaddq_f32(vmulq_f32(...)) I had)
                cur_result_vec = vmlaq_f32(cur_result_vec, m1_num_vector, m2_nums_vector);

                // stores result vector into the actual results vector
                vst1q_f32(&result[get_idx(outer_row, inner_col, size)], cur_result_vec);
            }

            // if have odd number of elements, will miss last few elements. manually loop
            if (inner_col < size) {
                for (; inner_col < size; inner_col++) {
                    float32_t m2_num = m2[get_idx(outer_col, inner_col, size)];

                    result[get_idx(outer_row, inner_col, size)] += m1_num * m2_num;
                }
            }

        }
    }
}