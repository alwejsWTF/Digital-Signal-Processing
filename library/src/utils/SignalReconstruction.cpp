#include "utils/SignalReconstruction.h"

std::pair<std::vector<double>, std::vector<double>> SignalReconstruction::zeroOrderHold(const std::vector<int>& quantizedSamples, const std::vector<double>& times) {
    std::vector<double> reconstructedSamples;
    std::vector<double> reconstructedTimes;

    for (size_t i = 0; i < quantizedSamples.size(); i++) {
        reconstructedSamples.push_back(static_cast<double>(quantizedSamples[i]));
        reconstructedTimes.push_back(times[i]);
    }

    return {reconstructedSamples, reconstructedTimes};
}


std::pair<std::vector<double>, std::vector<double>> SignalReconstruction::firstOrderHold(const std::vector<int>& quantizedSamples, const std::vector<double>& times) {
    std::vector<double> reconstructed;
    std::vector<double> reconstructedTimes;

    for (size_t i = 0; i < quantizedSamples.size() - 1; i++) {
        double start = quantizedSamples[i];
        double end = quantizedSamples[i + 1];
        double time_step = (times[i + 1] - times[i]) / 10;  // Interpolacja pomiędzy próbkami

        for (double t = times[i]; t < times[i + 1]; t += time_step) {
            double slope = (end - start) / (times[i + 1] - times[i]);
            reconstructed.push_back(start + slope * (t - times[i]));
            reconstructedTimes.push_back(t);
        }
    }
    reconstructed.push_back(quantizedSamples.back());
    reconstructedTimes.push_back(times.back());

    return {reconstructed, reconstructedTimes};
}

std::vector<double> SignalReconstruction::sincInterpolation(const std::vector<int> &quantizedSamples, double samplingRate) {
    std::vector<double> reconstructed(quantizedSamples.size() * samplingRate);
    double T = 1.0 / samplingRate;

    for (size_t i = 0; i < reconstructed.size(); ++i) {
        double t = (double) i * T;
        double sum = 0.0;
        for (size_t n = 0; n < quantizedSamples.size(); ++n) {
            double tn = (double) n * T;
            sum += quantizedSamples[n] * sinc((t - tn) / T);
        }
        reconstructed[i] = sum;
    }
    return reconstructed;
}

double SignalReconstruction::sinc(double t) {
    if (t == 0.0) {
        return 1.0;
    }
    double pi_t = M_PI * t;
    return sin(pi_t) / pi_t;
}
