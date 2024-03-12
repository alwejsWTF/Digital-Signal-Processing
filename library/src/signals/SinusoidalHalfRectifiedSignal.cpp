#include "signals/SinusoidalHalfRectifiedSignal.h"
#include <cmath>

SinusoidalHalfRectifiedSignal::SinusoidalHalfRectifiedSignal(double amplitude, double term, double startTime, double duration) :
ContinuousSignal(amplitude, startTime, duration, [amplitude, term, startTime](const double t) {
    return 0.5 * amplitude * (std::sin((2 * M_PI / term) * (t - startTime))
           + std::abs(std::sin((2 * M_PI / term) * (t - startTime))));
}), term(term) {}

double SinusoidalHalfRectifiedSignal::getTerm() const {
    return term;
}

void SinusoidalHalfRectifiedSignal::setTerm(const double term) {
    this->term = term;
}