#include "signals/SinusoidalSignal.h"
#include <cmath>
#include <sstream>

SinusoidalSignal::SinusoidalSignal(double amplitude, double term, double startTime, double duration, double samplingRate)
: ContinuousSignal(amplitude, startTime, duration, samplingRate, [amplitude, term, startTime](const double t) {
    return amplitude * std::sin((2 * M_PI / term) * (t - startTime));
}), term(term) {}

double SinusoidalSignal::getTerm() const {
    return term;
}

void SinusoidalSignal::setTerm(const double term) {
    this->term = term;
}

std::string SinusoidalSignal::getSignalName() {
    std::stringstream chain;
    chain << "Sygnal sinusoidalny";
    return chain.str();
}

std::string SinusoidalSignal::getSignalType() {
    return "SinusoidalSignal";
}