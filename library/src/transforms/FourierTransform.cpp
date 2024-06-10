#include "transforms/FourierTransform.h"
#include <cmath>

std::vector<std::complex<double>> FourierTransform::computeDFT(const std::vector<double>& input) {
    int N = input.size();
    std::vector<std::complex<double>> output(N);
    //double angle = 2 * M_PI / N;
    //std::complex<double> W(cos(angle), sin(angle));
    for (size_t m = 0; m < N; ++m) {
        std::complex<double> sum(0.0, 0.0);
        for (size_t n = 0; n < N; ++n) {
            double angle = 2 * M_PI * m * n / N;
            sum += std::complex<double>(cos(angle), -sin(angle)) * input[n];
        }
        output[m] = sum;
    }
    return output;
}
