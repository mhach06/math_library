#ifndef FFT_H
#define FFT_H

#include <vector>
#include <complex>

// uses complex numbers: (In-Phase, Quadrature)
using Complex = std::complex<double>;

/*
FOR ALL INPUTS IN REGULAR FFT: 
- Time Domain:
    - Index represents unit of time
    - abs(I, Q) = Amplitude
    - In 5G, usually represents set of I/Q Data (In-Phase & Quadrature)

FOR ALL OUTPUTS OF REGULAR FFT:
- Frequency Domain
    - Index represents the frequency
    - Absolute value represents magnitude (Amplitude)
    - angle of complex number represents time-shift
*/

// basic dft
void dft(std::vector<Complex>& signal);

// optimized version 1
void fft_v1(std::vector<Complex>& signal);

// optimized version 2
void fft_v2(std::vector<Complex>& signal);

#endif