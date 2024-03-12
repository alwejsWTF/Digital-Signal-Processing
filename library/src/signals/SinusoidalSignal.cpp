#include "signals/SinusoidalSignal.h"
#include <cmath>

SinusoidalSignal::SinusoidalSignal(double amplitude, double term, double startTime, double duration) :
ContinuousSignal(startTime, duration, [amplitude, term, startTime](const double t) {
    return amplitude * std::sin((2 * M_PI / term) * (t - startTime));
}), amplitude(amplitude), term(term) {}

double SinusoidalSignal::getAmplitude() const {
    return amplitude;
}

double SinusoidalSignal::getTerm() const {
    return term;
}

void SinusoidalSignal::setAmplitude(const double amplitude) {
    this->amplitude = amplitude;
}

void SinusoidalSignal::setTerm(const double term) {
    this->term = term;
}