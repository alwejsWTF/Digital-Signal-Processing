#include "transforms/CosineTransform.h"
#include <cmath>

std::vector<std::complex<double>> CosineTransform::computeDCT(const std::vector<double> &input) {
    int N = input.size();
    std::vector<std::complex<double>> output(N);

    for (size_t m = 0; m < N; ++m) {
        std::complex<double> sum(0.0);
        for (size_t n = 0; n < N; ++n) {
            sum += input[n] * cos(M_PI * m * (2.0 * n + 1) / (2.0 * N));
        }
        output[m] = sum * sqrt(2.0 / N);
        if (m == 0) output[m] /= sqrt(2.0);
    }
    return output;
}

