#include "utils/convolution.h"
#include <cmath>
#include <algorithm>

std::pair<std::vector<double>, std::vector<double>> discreteConvolution(
        const std::vector<double>& h, double hDeltaT, const std::vector<double>& x, double xDeltaT) {

    double commonDeltaT = std::min(hDeltaT, xDeltaT);
    std::vector<double> resampledH = resample(h, hDeltaT, commonDeltaT);
    std::vector<double> resampledX = resample(x, xDeltaT, commonDeltaT);
    int M = resampledH.size();
    int N = resampledX.size();
    int convSize = N + M - 1;
    std::vector<double> result(convSize, 0.0);
    std::vector<double> timeVector(convSize, 0.0);

    for (int n = 0; n < convSize; ++n) {
        for (int k = 0; k < M; ++k) {
            if (n - k >= 0 && n - k < N) {
                result[n] += resampledH[k] * resampledX[n - k];
            }
        }
        timeVector[n] = n * commonDeltaT;
    }

    return {result, timeVector};
}

std::vector<double> resample(const std::vector<double>& signal, double originalDeltaT, double newDeltaT) {
    int originalSize = signal.size();
    double originalDuration = originalSize * originalDeltaT;
    int newSize = static_cast<int>(std::round(originalDuration / newDeltaT));
    std::vector<double> resampledSignal(newSize, 0.0);

    for (int i = 0; i < newSize; ++i) {
        double originalTime = i * newDeltaT;
        int lowerIndex = static_cast<int>(originalTime / originalDeltaT);
        int upperIndex = lowerIndex + 1;
        double t = (originalTime - lowerIndex * originalDeltaT) / originalDeltaT;

        if (upperIndex < originalSize) {
            resampledSignal[i] = (1 - t) * signal[lowerIndex] + t * signal[upperIndex];
        } else {
            resampledSignal[i] = signal[lowerIndex];
        }
    }

    return resampledSignal;
}