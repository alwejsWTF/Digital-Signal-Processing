#include "transforms/FourierTransform.h"
#include <cmath>

std::vector<std::complex<double>> FourierTransform::computeDFT(const std::vector<double>& input) {
    size_t N = input.size();
    std::vector<std::complex<double>> output(N);

    for (size_t k = 0; k < N; ++k) {
        std::complex<double> sum(0.0, 0.0);
        for (size_t n = 0; n < N; ++n) {
            double angle = 2 * M_PI * k * n / N;
            sum += input[n] * std::complex<double>(cos(angle), -sin(angle));
        }
        output[k] = sum;
    }
    return output;
}
