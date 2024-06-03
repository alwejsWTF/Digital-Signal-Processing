#include "utils/crossCorrelation.h"
#include "utils/convolution.h"

std::pair<std::vector<double>, std::vector<double>> directCrossCorrelation(
        const std::vector<double>& h, double hDeltaT, const std::vector<double>& x, double xDeltaT) {

    double commonDeltaT = std::min(hDeltaT, xDeltaT);
    std::vector<double> resampledH = resample(h, hDeltaT, commonDeltaT);
    std::vector<double> resampledX = resample(x, xDeltaT, commonDeltaT);
    int M = resampledH.size();
    int N = resampledX.size();
    int corrSize = N + M - 1;
    std::vector<double> result(corrSize, 0.0);
    std::vector<double> timeVector(corrSize, 0.0);

    for (int n = 0; n < corrSize; ++n) {
        for (int k = 0; k < M; ++k) {
            if (n - k >= 0 && n - k < N) {
                result[n] += resampledH[k] * resampledX[k - n];
            }
        }
        timeVector[n] = n * commonDeltaT;
    }

    return {result, timeVector};
}


//std::vector<double> convolutionCrossCorrelation(const std::vector<double>& h, const std::vector<double>& x) {
//    std::vector<double> h_reversed(h.rbegin(), h.rend());
//    return discreteConvolution(h_reversed, x);
//}