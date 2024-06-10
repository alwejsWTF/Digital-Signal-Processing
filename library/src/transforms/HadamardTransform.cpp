#include "transforms/HadamardTransform.h"
#include <cmath>

typedef std::vector<std::vector<double>> Matrix;

Matrix generateMatrix(int order) {
    if (order == 0) return {{1}};

    Matrix H = generateMatrix(order - 1);
    int size = H.size();
    Matrix Hm(2 * size, std::vector<double>(2 * size));

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            double h = H[i][j] / sqrt(2);
            Hm[i][j] = h;
            Hm[i][j + size] = h;
            Hm[i + size][j] = h;
            Hm[i + size][j + size] = -h;
        }
    }
    return Hm;
}

std::vector<std::complex<double>> HadamardTransform::computeHadamard(const std::vector<double>& input) {
    int m = (int) round(log(input.size()) / log(2.0));
    Matrix H = generateMatrix(m);
    int N = H.size();
    std::vector<std::complex<double>> X(N, 0.0);

    for (int i = 0; i < N; ++i) {
        std::complex<double> sum(0.0);
        for (int j = 0; j < N; ++j) {
            sum += H[i][j] * input[j];
        }
        X[i] = sum;
    }
    return X;
}