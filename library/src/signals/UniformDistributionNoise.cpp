#include "signals/UniformDistributionNoise.h"
#include <random>
#include <sstream>

UniformDistributionNoise::UniformDistributionNoise(double amplitude, double startTime, double duration, double samplingRate)
: ContinuousSignal(amplitude, startTime, duration, samplingRate, nullptr) {}

void UniformDistributionNoise::generate() {
    data.clear();
    time.clear();
    std::random_device rd;  // Seed for the random number engine
    std::mt19937 gen(rd()); // Standard mersenne_twister_engine
    std::uniform_real_distribution<> dis(-amplitude, amplitude);
    const int sampleCount = static_cast<int>(samplingRate * duration);
    data.reserve(sampleCount);

    for (int i = 0; i < sampleCount; ++i) {
        const double t = i / samplingRate + startTime;
        time.push_back(t);
        double noiseValue = dis(gen);
        data.push_back(noiseValue);
    }
}

std::string UniformDistributionNoise::getSignalName() {
    std::stringstream chain;
    chain << "Szum o rozkladzie jednostajnym";
    return chain.str();
}


