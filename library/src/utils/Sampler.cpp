#include "utils/Sampler.h"

std::pair<std::vector<double>, std::vector<double>> Sampler::uniformSample(const std::vector<double>& times, const std::vector<double>& samples, double samplingRate) {
    std::vector<double> sampledSamples;
    std::vector<double> sampledTimes;
    double samplingInterval = 1.0 / samplingRate;

    for (size_t i = 0; i < samples.size(); i += static_cast<int>(1 / samplingInterval)) {
        sampledSamples.push_back(samples[i]);
        sampledTimes.push_back(times[i]);
    }
    return {sampledSamples, sampledTimes};
}

