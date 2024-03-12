#include "signals/RectangularSignal.h"
#include <cmath>

RectangularSignal::RectangularSignal(double amplitude, double term, double dutyCycle, double startTime, double duration)
: ContinuousSignal(startTime, duration, [amplitude, term, dutyCycle, startTime](const double t) {
    return std::fmod(t - startTime, term) < dutyCycle * term? amplitude : 0;
}), amplitude(amplitude), term(term), dutyCycle(dutyCycle) {}
