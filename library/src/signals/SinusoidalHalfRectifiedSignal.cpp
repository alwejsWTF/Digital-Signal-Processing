#include "signals/SinusoidalHalfRectifiedSignal.h"
#include <cmath>

SinusoidalHalfRectifiedSignal::SinusoidalHalfRectifiedSignal(double amplitude, double term, double startTime, double duration) :
ContinuousSignal(startTime, duration, [amplitude, term, startTime](const double t) {
    return 0.5 * amplitude * (std::sin((2 * M_PI / term) * (t - startTime))
           + std::abs(std::sin((2 * M_PI / term) * (t - startTime))));
}), amplitude(amplitude), term(term) {}

void SinusoidalHalfRectifiedSignal::generate() {
    constexpr double samplingRate = 100;
    const int sampleCount = static_cast<int>(samplingRate * duration);
    for(int i = 0; i < sampleCount; ++i) {
        const double t = i / samplingRate;
        data.push_back(signalFunction(t));
    }
}

double SinusoidalHalfRectifiedSignal::getAmplitude() const {
    return amplitude;
}

double SinusoidalHalfRectifiedSignal::getTerm() const {
    return term;
}

void SinusoidalHalfRectifiedSignal::setAmplitude(const double amplitude) {
    this->amplitude = amplitude;
}

void SinusoidalHalfRectifiedSignal::setTerm(const double term) {
    this->term = term;
}