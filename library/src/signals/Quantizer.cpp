#include <algorithm>
#include <cmath>
#include "signals/Quantizer.h"

std::vector<double> Quantizer::uniformQuantizeRounded(const std::vector<double>& samples, int levels) {
    double minVal = *std::min_element(samples.begin(), samples.end());
    double maxVal = *std::max_element(samples.begin(), samples.end());
    double step = (maxVal - minVal) / (levels - 1);

    std::vector<double> quantized;
    quantized.reserve(samples.size());

    for (double sample : samples) {
        double quantizedValue = std::round((sample - minVal) / step) * step + minVal;
        quantized.push_back(quantizedValue);
    }
    return quantized;
}
