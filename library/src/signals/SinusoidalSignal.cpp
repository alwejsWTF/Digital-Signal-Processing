#include "signals/SinusoidalSignal.h"
#include <cmath>

SinusoidalSignal::SinusoidalSignal(double amplitude, double term, double startTime, double duration) :
ContinuousSignal(amplitude, startTime, duration, [amplitude, term, startTime](const double t) {
    return amplitude * std::sin((2 * M_PI / term) * (t - startTime));
}), term(term) {}

double SinusoidalSignal::getTerm() const {
    return term;
}

void SinusoidalSignal::setTerm(const double term) {
    this->term = term;
}