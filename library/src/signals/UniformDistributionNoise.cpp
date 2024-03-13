#include "signals/UniformDistributionNoise.h"
#include <random>

UniformDistributionNoise::UniformDistributionNoise(double amplitude, double startTime, double duration)
: ContinuousSignal(amplitude, startTime, duration, nullptr) {}

void UniformDistributionNoise::generate(double samplingRate) {
    std::random_device rd;  // Seed for the random number engine
    std::mt19937 gen(rd()); // Standard mersenne_twister_engine
    std::uniform_real_distribution<> dis(-amplitude, amplitude);
    const int sampleCount = static_cast<int>(samplingRate * duration);
    data.reserve(sampleCount);

    for (int i = 0; i <= sampleCount; ++i) {
        const double t = i / samplingRate + startTime;
        time.push_back(t);
        double noiseValue = dis(gen);
        data.push_back(noiseValue); // Generate a random value in the range [-Amax, Amax]
    }
}


