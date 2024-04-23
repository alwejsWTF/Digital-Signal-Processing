#include "signals/SignalReconstruction.h"
#include <cmath>
#include <iostream>

std::pair<std::vector<double>, std::vector<double>> SignalReconstruction::reconstructZOH(
        const std::vector<double>& samples,
        double originalSamplingRate,
        int reconstructionMultiplier
   ) {
    double reconstructionSamplingRate = originalSamplingRate * reconstructionMultiplier;
    double reconstructionInterval = 1.0 / reconstructionSamplingRate;

    std::vector<double> reconstructed(samples.size() * reconstructionMultiplier);
    std::vector<double> time(reconstructed.size());

    for (size_t i = 0, j = 0; i < samples.size(); ++i) {
        for (int k = 0; k < reconstructionMultiplier; ++k, ++j) {
            reconstructed[j] = samples[i];
            time[j] = j * reconstructionInterval;
        }
    }
    return {reconstructed, time};
}

std::pair<std::vector<double>, std::vector<double>> SignalReconstruction::reconstructFOH(
        const std::vector<double>& samples,
        const std::vector<double>& time,
        double originalSamplingRate,
        int reconstructionMultiplier
) {
    double reconstructionSamplingRate = originalSamplingRate * reconstructionMultiplier;
    double reconstructionInterval = 1.0 / reconstructionSamplingRate;

    std::vector<double> reconstructed(samples.size() * reconstructionMultiplier - reconstructionMultiplier);
    std::vector<double> reconstructedTime(time.size() * reconstructionMultiplier - reconstructionMultiplier);

    for (size_t i = 0, j = 0; i < samples.size() - 1; ++i) {
        double currentValue = samples[i];
        double nextValue = samples[i + 1];
        double step = (nextValue - currentValue) / reconstructionMultiplier;
        for (int k = 0; k < reconstructionMultiplier; ++k, ++j) {
            reconstructed[j] = currentValue + step * k;
            reconstructedTime[j] = reconstructionInterval * j;
        }
    }
    return {reconstructed, reconstructedTime};
}

std::pair<std::vector<double>, std::vector<double>> SignalReconstruction::reconstructSinc(
        const std::vector<double>& samples,
        const std::vector<double>& originalTime
) {
    std::vector<double> reconstructed;
    std::vector<double> time;

    return {reconstructed, time};
}
