#include "signals/SinusoidalHalfRectifiedSignal.h"
#include <cmath>
#include <sstream>

SinusoidalHalfRectifiedSignal::SinusoidalHalfRectifiedSignal(double amplitude, double term, double startTime, double duration, double samplingRate)
: ContinuousSignal(amplitude, startTime, duration, samplingRate, [amplitude, term, startTime](const double t) {
    return 0.5 * amplitude * (std::sin((2 * M_PI / term) * (t - startTime))
           + std::abs(std::sin((2 * M_PI / term) * (t - startTime))));
}), term(term) {}

double SinusoidalHalfRectifiedSignal::getTerm() const {
    return term;
}

void SinusoidalHalfRectifiedSignal::setTerm(const double term) {
    this->term = term;
}

std::string SinusoidalHalfRectifiedSignal::getSignalName() {
    std::stringstream chain;
    chain << "Sygnal sinusoidalny wyprostowany jednopolowkowo";
    return chain.str();
}

std::string SinusoidalHalfRectifiedSignal::getSignalType() {
    return "SinusoidalHalfRectifiedSignal";
}