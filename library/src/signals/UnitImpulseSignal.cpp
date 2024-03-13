#include "signals/UnitImpulseSignal.h"

UnitImpulseSignal::UnitImpulseSignal(double amplitude, double startTime, double duration, int stepSampleNumber, int firstSample)
: DiscreteSignal(amplitude, startTime, duration, nullptr), stepSampleNumber(stepSampleNumber), firstSample(firstSample) {}

void UnitImpulseSignal::generate(double samplingRate) {
    const int sampleCount = static_cast<int>(samplingRate * duration);
    data.resize(sampleCount, 0);
    int impulseIndex = stepSampleNumber - firstSample;
    if (impulseIndex >= 0 && impulseIndex < data.size()) {
        data[impulseIndex] = amplitude;
    }
    for (int i = firstSample; i <= sampleCount + firstSample; ++i) {
        const double t = i / samplingRate + startTime;
        time.push_back(t);
    }
}

