#include "signals/RectangularSymmetricSignal.h"
#include <cmath>

RectangularSymmetricSignal::RectangularSymmetricSignal(double amplitude, double term, double dutyCycle, double startTime, double duration)
: ContinuousSignal(startTime, duration, [amplitude, term, dutyCycle, startTime](const double t)
    { return std::fmod((t - startTime), term) < dutyCycle * term ? amplitude : -amplitude; }), amplitude(amplitude),
term(term), dutyCycle(dutyCycle) {}

void RectangularSymmetricSignal::generate() {
    constexpr double samplingRate = 100;
    const int sampleCount = static_cast<int>(samplingRate * duration);
    for (int i = 0; i < sampleCount; ++i) {
        const double t = i / samplingRate;
        data.push_back(signalFunction(t));
    }
}