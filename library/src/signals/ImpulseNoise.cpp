#include "signals/ImpulseNoise.h"
#include <random>

ImpulseNoise::ImpulseNoise(double amplitude, double startTime, double duration, double probability)
: DiscreteSignal(amplitude, startTime, duration, nullptr), probability(probability) {}

void ImpulseNoise::generate(double samplingRate) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::bernoulli_distribution dis(probability);
    const int sampleCount = static_cast<int>(samplingRate * duration);
    data.reserve(sampleCount);

    for (int i = 0; i <= sampleCount; ++i) {
        const double t = i / samplingRate + startTime;
        time.push_back(t);
        data.push_back(dis(gen) ? amplitude : 0.0);
    }
}

