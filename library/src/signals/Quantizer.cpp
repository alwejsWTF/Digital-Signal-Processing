#include <algorithm>
#include <cmath>
#include "signals/Quantizer.h"

std::vector<double> Quantizer::uniformQuantize(const std::vector<double>& samples, int levels, bool flag) {
    double minVal = *std::min_element(samples.begin(), samples.end());
    double maxVal = *std::max_element(samples.begin(), samples.end());
    double step = (maxVal - minVal) / (levels - 1);

    std::vector<double> quantized;
    quantized.reserve(samples.size());

    double quantizedValue;
    for (double sample : samples) {
        if (flag)
            quantizedValue = std::round((sample - minVal) / step) * step + minVal;
        else
            quantizedValue = std::floor((sample - minVal) / step) * step + minVal;
        quantized.push_back(quantizedValue);
    }
    return quantized;
}
