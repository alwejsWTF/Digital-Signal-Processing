#include "signals/SinusoidalFullRectifiedSignal.h"
#include <cmath>

SinusoidalFullRectifiedSignal::SinusoidalFullRectifiedSignal(double amplitude, double term, double startTime, double duration) :
ContinuousSignal(startTime, duration, [amplitude, term, startTime](const double t)
    { return amplitude * std::abs(std::sin((2 * M_PI / term) * (t - startTime)));
    }), amplitude(amplitude), term(term) {}

void SinusoidalFullRectifiedSignal::generate() {
    constexpr double samplingRate = 100;
    const int sampleCount = static_cast<int>(samplingRate * duration);
    for(int i = 0; i < sampleCount; ++i) {
        const double t = i / samplingRate;
        data.push_back(signalFunction(t));
    }
}

double SinusoidalFullRectifiedSignal::getAmplitude() const {
    return amplitude;
}

double SinusoidalFullRectifiedSignal::getTerm() const {
    return term;
}

void SinusoidalFullRectifiedSignal::setAmplitude(const double amplitude) {
    this->amplitude = amplitude;
}

void SinusoidalFullRectifiedSignal::setTerm(const double term) {
    this->term = term;
}