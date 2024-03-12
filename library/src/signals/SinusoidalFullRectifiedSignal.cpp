#include "signals/SinusoidalFullRectifiedSignal.h"
#include <cmath>

SinusoidalFullRectifiedSignal::SinusoidalFullRectifiedSignal(double amplitude, double term, double startTime, double duration) :
ContinuousSignal(amplitude, startTime, duration, [amplitude, term, startTime](const double t) {
    return amplitude * std::abs(std::sin((2 * M_PI / term) * (t - startTime)));
}), term(term) {}

double SinusoidalFullRectifiedSignal::getTerm() const {
    return term;
}

void SinusoidalFullRectifiedSignal::setTerm(const double term) {
    this->term = term;
}