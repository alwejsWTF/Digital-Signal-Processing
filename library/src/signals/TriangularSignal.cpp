#include "signals/TriangularSignal.h"
#include <cmath>

TriangularSignal::TriangularSignal(double amplitude, double term, double dutyCycle, double startTime, double duration)
: ContinuousSignal(startTime, duration, [amplitude, term, dutyCycle, startTime](const double t) {
    double timeInTerm = std::fmod(t - startTime, term);
    return timeInTerm < dutyCycle * term
        ? amplitude / (dutyCycle * term) * timeInTerm
        : amplitude / (1 - dutyCycle) * (-timeInTerm / term + 1);
}), amplitude(amplitude), term(term), dutyCycle(dutyCycle) {}

void TriangularSignal::generate() {
    constexpr double samplingRate = 100;
    const int sampleCount = static_cast<int>(samplingRate * duration);
    for (int i = 0; i < sampleCount; ++i) {
        const double t = i / samplingRate;
        data.push_back(signalFunction(t));
    }
}