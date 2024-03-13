#include "signals/GaussianNoise.h"
#include <random>

GaussianNoise::GaussianNoise(double amplitude, double startTime, double duration)
: ContinuousSignal(amplitude, startTime, duration, nullptr) {}

void GaussianNoise::generate(double samplingRate) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<> dis(0, 1);
    const int sampleCount = static_cast<int>(samplingRate * duration);
    data.reserve(sampleCount);

    for (int i = 0; i <= sampleCount; ++i) {
        const double t = i / samplingRate + startTime;
        time.push_back(t);
        double noiseValue = dis(gen);
        data.push_back(amplitude * noiseValue);
    }
}

