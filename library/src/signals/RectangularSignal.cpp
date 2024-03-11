#include "signals/RectangularSignal.h"
#include <cmath>

RectangularSignal::RectangularSignal(double amplitude, double term, double dutyCycle, double startTime, double duration)
: ContinuousSignal(startTime, duration, [amplitude, term, dutyCycle, startTime](const double t)
    { return std::fmod((t - startTime), term) < dutyCycle * term ? amplitude : 0; }), amplitude(amplitude),
term(term), dutyCycle(dutyCycle) {}

void RectangularSignal::generate() {
    constexpr double samplingRate = 100;
    const int sampleCount = static_cast<int>(samplingRate * duration);
    for (int i = 0; i < sampleCount; ++i) {
        const double t = i / samplingRate;
        data.push_back(signalFunction(t));
    }
}