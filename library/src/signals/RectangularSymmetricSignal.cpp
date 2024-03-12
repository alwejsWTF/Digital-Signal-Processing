#include "signals/RectangularSymmetricSignal.h"
#include <cmath>

RectangularSymmetricSignal::RectangularSymmetricSignal(double amplitude, double term, double dutyCycle, double startTime, double duration)
: ContinuousSignal(amplitude, startTime, duration, [amplitude, term, dutyCycle, startTime](const double t) {
    return std::fmod((t - startTime), term) < dutyCycle * term ? amplitude : -amplitude;
}), term(term), dutyCycle(dutyCycle) {}
