#include "signals/SinusoidalFullRectifiedSignal.h"
#include <cmath>
#include <sstream>

SinusoidalFullRectifiedSignal::SinusoidalFullRectifiedSignal(double amplitude, double term, double startTime, double duration, double samplingRate)
: ContinuousSignal(amplitude, startTime, duration, samplingRate, [amplitude, term, startTime](const double t) {
    return amplitude * std::abs(std::sin((2 * M_PI / term) * (t - startTime)));
}), term(term) {}

double SinusoidalFullRectifiedSignal::getTerm() const {
    return term;
}

void SinusoidalFullRectifiedSignal::setTerm(const double term) {
    this->term = term;
}

std::string SinusoidalFullRectifiedSignal::getSignalName() {
    std::stringstream chain;
    chain << "Sygnal sinusoidalny wyprostowany dwupolowkowo";
    return chain.str();
}