#include <algorithm>
#include "utils/Quantizer.h"

std::vector<int> Quantizer::uniformQuantize(const std::vector<double>& samples, int levels) {
    double minVal = *std::min_element(samples.begin(), samples.end());
    double maxVal = *std::max_element(samples.begin(), samples.end());
    double step = (maxVal - minVal) / levels;

    std::vector<int> quantized(samples.size());
    for (size_t i = 0; i < samples.size(); ++i) {
        int level = static_cast<int>((samples[i] - minVal) / step);
        quantized[i] = std::min(level, levels - 1);
    }
    return quantized;
}
