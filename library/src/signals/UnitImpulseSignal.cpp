#include "signals/UnitImpulseSignal.h"
#include <sstream>

UnitImpulseSignal::UnitImpulseSignal(double amplitude, double startTime, double duration, double samplingRate, int stepSampleNumber, int firstSample)
: DiscreteSignal(amplitude, startTime, duration, samplingRate, nullptr), stepSampleNumber(stepSampleNumber), firstSample(firstSample) {}

void UnitImpulseSignal::generate() {
    const int sampleCount = static_cast<int>(samplingRate * duration);
    data.resize(sampleCount, 0);
    int impulseIndex = stepSampleNumber - firstSample;
    if (impulseIndex >= 0 && impulseIndex < data.size()) {
        data[impulseIndex] = amplitude;
    }
    for (int i = firstSample; i < sampleCount + firstSample; ++i) {
        const double t = i / samplingRate + startTime;
        time.push_back(t);
    }
}

std::string UnitImpulseSignal::getSignalName() {
    std::stringstream chain;
    chain << "Impuls jednostkowy";
    return chain.str();
}

