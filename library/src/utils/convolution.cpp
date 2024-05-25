#include "utils/convolution.h"

std::vector<double> discreteConvolution(const std::vector<double>& h, const std::vector<double>& x) {
    int M = h.size();
    int N = x.size();
    int convSize = N + M - 1;
    std::vector<double> result(convSize, 0.0);

    for (int n = 0; n < convSize; ++n) {
        for (int k = 0; k < M; ++k) {
            if (n - k >= 0 && n - k < N) {
                result[n] += h[k] * x[n - k];
            }
        }
    }

    return result;
}

