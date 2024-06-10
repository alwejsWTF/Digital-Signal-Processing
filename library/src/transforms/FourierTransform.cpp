#include "transforms/FourierTransform.h"
#include <cmath>

std::vector<std::complex<double>> FourierTransform::computeFFT(const std::vector<std::complex<double>>& input, bool invert) {
    int N = input.size();
    if (N <= 1) return input;

    std::vector<std::complex<double>> even(N / 2), odd(N / 2);
    for (int i = 0, j = 0; i < N / 2; i += 2, ++j) {
        even[j] = input[i];
        odd[j] = input[i + 1];
    }

    std::vector<std::complex<double>> F_even = computeFFT(even, invert);
    std::vector<std::complex<double>> F_odd = computeFFT(odd, invert);

    double angle = 2 * M_PI / N * (invert ? -1 : 1);
    std::complex<double> w(1), wn(cos(angle), sin(angle));
    std::vector<std::complex<double>> F(N);
    for (int k = 0; k < N / 2; ++k) {
        F[k] = F_even[k] + w * F_odd[k];
        F[k + N / 2] = F_even[k] - w * F_odd[k];
        if (invert) {
            F[k] /= 2;
            F[k + N / 2] /= 2;
        }
        w *= wn;
    }
    return F;
}

std::vector<std::complex<double>> FourierTransform::computeDFT(const std::vector<double>& input) {
    int N = input.size();
    std::vector<std::complex<double>> output(N);
    //double angle = 2 * M_PI / N;
    //std::complex<double> W(cos(angle), sin(angle));
    for (size_t m = 0; m < N; ++m) {
        std::complex<double> sum(0.0, 0.0);
        for (size_t n = 0; n < N; ++n) {
            double angle = 2 * M_PI * m * n / N;
            sum += std::complex<double>(cos(angle), sin(angle)) * input[n];
        }
        output[m] = sum;
    }
    return output;
}
