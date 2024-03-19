#include "signals/GaussianNoise.h"
#include <random>
#include <sstream>

GaussianNoise::GaussianNoise(double amplitude, double startTime, double duration, double samplingRate)
: ContinuousSignal(amplitude, startTime, duration, samplingRate, nullptr) {}

void GaussianNoise::generate() {
    data.clear();
    time.clear();
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<> dis(0, 1);
    const int sampleCount = static_cast<int>(samplingRate * duration);
    data.reserve(sampleCount);

    for (int i = 0; i < sampleCount; ++i) {
        const double t = i / samplingRate + startTime;
        time.push_back(t);
        double noiseValue = dis(gen);
        data.push_back(amplitude * noiseValue);
    }
}

std::string GaussianNoise::getSignalName() {
    std::stringstream chain;
    chain << "Szum gaussowski";
    return chain.str();
}

