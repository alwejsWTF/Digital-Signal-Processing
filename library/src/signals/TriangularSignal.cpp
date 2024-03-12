#include "signals/TriangularSignal.h"
#include <cmath>

TriangularSignal::TriangularSignal(double amplitude, double term, double dutyCycle, double startTime, double duration)
: ContinuousSignal(startTime, duration, [amplitude, term, dutyCycle, startTime](const double t) {
    double timeInTerm = std::fmod(t - startTime, term); // t-t1 - floor((t-t1)/T) * T  || t-kT-t1
    return timeInTerm < dutyCycle * term
        ? (amplitude / (dutyCycle * term)) * timeInTerm
        : ((-amplitude / (term * (1-dutyCycle))) * timeInTerm) + (amplitude/(1-dutyCycle));
//        amplitude / (1 - dutyCycle) * (-timeInTerm / term + 1);
}), amplitude(amplitude), term(term), dutyCycle(dutyCycle) {}
