#include "utils/crossCorrelation.h"
#include "utils/convolution.h"

std::vector<double> directCrossCorrelation(const std::vector<double>& h, const std::vector<double>& x) {
    int M = h.size();
    int N = x.size();
    int corrSize = N + M - 1;
    std::vector<double> result(corrSize, 0.0);

    for (int n = 0; n < corrSize; ++n) {
        for (int k = 0; k < M; ++k) {
            if (n + k >= 0 && n + k < N) {
                result[n] += h[k] * x[n - k];
            }
        }
    }

    return result;
}

//std::vector<double> convolutionCrossCorrelation(const std::vector<double>& h, const std::vector<double>& x) {
//    std::vector<double> h_reversed(h.rbegin(), h.rend());
//    return discreteConvolution(h_reversed, x);
//}