#include "transforms/FourierTransform.h"
#include <cmath>
#include <algorithm>

std::vector<std::complex<double>> FourierTransform::computeDITFFT(const std::vector<std::complex<double>>& input) {
    int N = input.size();
    if (N <= 1) return input;

    std::vector<std::complex<double>> even(N / 2), odd(N / 2);
    for (int i = 0; i < N / 2; ++i) {
        even[i] = input[2 * i];
        odd[i] = input[2 * i + 1];
    }

    std::vector<std::complex<double>> F_even = computeDITFFT(even);
    std::vector<std::complex<double>> F_odd = computeDITFFT(odd);

    std::vector<std::complex<double>> F(N);
    for (int k = 0; k < N / 2; ++k) {
        std::complex<double> t = std::polar(1.0, -2 * M_PI * k / N) * F_odd[k];
        F[k] = F_even[k] + t;
        F[k + N / 2] = F_even[k] - t;
    }
    return F;
}

std::vector<std::complex<double>> FourierTransform::computeDIFFFT(const std::vector<std::complex<double>>& input) {
    int N = input.size();
    if (N <= 1) return input;

    for (int i = 0, j = 0; i < N; ++i) {
        if (j > i) {
            std::vector<std::complex<double>> tmp;
            tmp.push_back(input[i]) ;
            input[j].   push_back(tmp);
        } std::swap(input[i], input[j]);
        int m = N;
        while (m >= 2 && j >= (m >>= 1)) {
            j -= m;
        }
        j += m;
    }

    for (int len = 2; len <= N; len <<= 1) {
        double angle = -2 * M_PI / len;
        std::complex<double> wlen(cos(angle), sin(angle));
        for (int i = 0; i < N; i += len) {
            std::complex<double> w(1);
            for (int j = 0; j < len / 2; ++j) {
                std::complex<double> u = input[i + j];
                std::complex<double> v = input[i + j + len / 2] * w;
                input[i + j] = u + v;
                input[i + j + len / 2] = u - v;
                w *= wlen;
            }
        }
    }
    return input;
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
