#include "signals/SignalReconstruction.h"
#include <cmath>

std::pair<std::vector<double>, std::vector<double>> SignalReconstruction::reconstructZOH(
        const std::vector<double>& samples,
        double startTime,
        double originalSamplingRate,
        int reconstructionMultiplier
   ) {
    double reconstructionSamplingRate = originalSamplingRate * reconstructionMultiplier;
    double reconstructionInterval = 1.0 / reconstructionSamplingRate;

    std::vector<double> reconstructed(samples.size() * reconstructionMultiplier);
    std::vector<double> reconstructedTime(reconstructed.size());

    for (size_t i = 0, j = 0; i < samples.size(); ++i) {
        for (int k = 0; k < reconstructionMultiplier; ++k, ++j) {
            reconstructed[j] = samples[i];
            reconstructedTime[j] = startTime + j * reconstructionInterval;
        }
    }
    return {reconstructed, reconstructedTime};
}

std::pair<std::vector<double>, std::vector<double>> SignalReconstruction::reconstructFOH(
        const std::vector<double>& samples,
        double startTime,
        double originalSamplingRate,
        int reconstructionMultiplier
) {
    double reconstructionSamplingRate = originalSamplingRate * reconstructionMultiplier;
    double reconstructionInterval = 1.0 / reconstructionSamplingRate;

    std::vector<double> reconstructed(samples.size() * reconstructionMultiplier - reconstructionMultiplier);
    std::vector<double> reconstructedTime(samples.size() * reconstructionMultiplier - reconstructionMultiplier);

    for (size_t i = 0, j = 0; i < samples.size() - 1; ++i) {
        double currentValue = samples[i];
        double nextValue = samples[i + 1];
        double step = (nextValue - currentValue) / reconstructionMultiplier;
        for (int k = 0; k < reconstructionMultiplier; ++k, ++j) {
            reconstructed[j] = currentValue + step * k;
            reconstructedTime[j] = startTime + reconstructionInterval * j;
        }
    }
    return {reconstructed, reconstructedTime};
}

std::pair<std::vector<double>, std::vector<double>> SignalReconstruction::reconstructSinc(
        const std::vector<double>& samples,
        double startTime,
        double originalSamplingRate,
        int reconstructionMultiplier
) {
    double reconstructionSamplingRate = originalSamplingRate * reconstructionMultiplier;
    double reconstructionInterval = 1.0 / reconstructionSamplingRate;

    std::vector<double> reconstructed(samples.size() * reconstructionMultiplier);
    std::vector<double> reconstructedTime(samples.size() * reconstructionMultiplier);

    for (int i = 0; i < samples.size() * reconstructionMultiplier; ++i) {
        double t = startTime + i * reconstructionInterval;
        reconstructedTime[i] = t;
        for (size_t j = 0; j < samples.size(); ++j) {
            double sincArgument = M_PI * (t * originalSamplingRate - j);
            double sincValue = (sincArgument == 0) ? 1.0 : std::sin(sincArgument) / sincArgument;
            reconstructed[i] += samples[j] * sincValue;
        }
    }
    return {reconstructed, reconstructedTime};
}

