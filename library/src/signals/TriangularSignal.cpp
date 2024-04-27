#include "signals/TriangularSignal.h"
#include <cmath>
#include <sstream>

TriangularSignal::TriangularSignal(double amplitude, double term, double dutyCycle, double startTime, double duration, double samplingRate)
: ContinuousSignal(amplitude, startTime, duration, samplingRate, [amplitude, term, dutyCycle, startTime](const double t) {
    double timeInTerm = std::fmod(t - startTime, term);
    return timeInTerm < dutyCycle * term
        ? amplitude / (dutyCycle * term) * timeInTerm
        : amplitude / (1 - dutyCycle) * (-timeInTerm / term + 1);
}), term(term), dutyCycle(dutyCycle) {}

std::string TriangularSignal::getSignalName() {
    std::stringstream chain;
    chain << "Sygnal trojkatny";
    return chain.str();
}

double TriangularSignal::getTerm() const {
    return term;
}

double TriangularSignal::getDutyCycle() const {
    return dutyCycle;
}
