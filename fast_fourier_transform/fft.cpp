#include "fft.h"

void dft(std::vector<Complex>& signal) {
    /*
    SIMPLIFIED BASE DFT EQUATION FROM:
        X_k = sum{n=0 to N-1} x_n * e^{-j * (2 * pi)/N * k * n}
    TO THE FOLLOWING FORM. USES EULER'S FORMULA: e^{-j * theta} = cos(theta) - j * sin(theta)
        X_k = sum{n=0 to N-1} x_n * (cos(theta) - j * sin(theta)) : theta = ((2 * pi) / N) * k * n
    */
    int N = signal.size();
    std::vector<Complex> output(N, {0.0, 0.0}); // avoids overriding values still needed in signal.

    for (int freq_bin = 0; freq_bin < N; freq_bin++) {
        int k = freq_bin;
        std::complex<double> bin_k = {0, 0}; // X_k
        for (int time_sample = 0; time_sample < N; time_sample++) {
            int n = time_sample;

            double theta = -2.0 * std::acos(-1.0) * k * n / N; // Using acos(-1.0) for Pi (since old version of c++)
            std::complex<double> multiplier(std::cos(theta), std::sin(theta)); // Now matches the variable name

            bin_k += signal[n] * multiplier;
        }
        output[k] = bin_k;
    }
    signal = output;
}


void fft_v1(std::vector<Complex> signal) {

}


void fft_v2(std::vector<Complex> signal) {

}
