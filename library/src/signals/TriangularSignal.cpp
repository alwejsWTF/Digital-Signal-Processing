#include "signals/TriangularSignal.h"
#include <cmath>

TriangularSignal::TriangularSignal(double amplitude, double term, double dutyCycle, double startTime, double duration)
: ContinuousSignal(amplitude, startTime, duration, [amplitude, term, dutyCycle, startTime](const double t) {
    double timeInTerm = std::fmod(t - startTime, term);
    return timeInTerm < dutyCycle * term
        ? amplitude / (dutyCycle * term) * timeInTerm
        : amplitude / (1 - dutyCycle) * (-timeInTerm / term + 1);
}), term(term), dutyCycle(dutyCycle) {}
