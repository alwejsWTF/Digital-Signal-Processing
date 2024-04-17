#include "utils/Measures.h"
#include <cmath>
#include <algorithm>

double Measures::meanSquaredError(const std::vector<double> &original, const std::vector<double> &reconstructed) {
    double sum = 0.0;
    for (size_t i = 0; i < original.size(); ++i) {
        double diff = original[i] - reconstructed[i];
        sum += diff * diff;
    }
    return sum / static_cast<double>(original.size());
}

double Measures::signalToNoiseRatio(const std::vector<double> &original, const std::vector<double> &reconstructed) {
    double signalPower = 0.0, noise, noisePower = 0.0;
    for (size_t i = 0; i < original.size(); ++i) {
        signalPower += original[i] * original[i];
        noise = original[i] - reconstructed[i];
        noisePower += noise * noise;
    }
    return 10 * log10(signalPower / noisePower);
}

double Measures::peakSignalToNoiseRatio(const std::vector<double> &original, const std::vector<double> &reconstructed) {
    double mse = meanSquaredError(original, reconstructed);
    double maxSignal = *std::max_element(original.begin(), original.end());
    return 10 * log10(maxSignal / mse);
}

double Measures::maximumDifference(const std::vector<double> &original, const std::vector<double> &reconstructed) {
    double maxDiff = 0.0;
    for (size_t i = 0; i < original.size(); ++i) {
        double diff = std::abs(original[i] - reconstructed[i]);
        if (diff > maxDiff) {
            maxDiff = diff;
        }
    }
    return maxDiff;
}
