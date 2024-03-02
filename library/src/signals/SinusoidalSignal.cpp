#include "signals/SinusoidalSignal.h"
#include <iostream>
#include <cmath>

SinusoidalSignal::SinusoidalSignal(double amplitude, double term, double startTime, double duration) :
amplitude(amplitude), term(term), startTime(startTime), duration(duration) {}

void SinusoidalSignal::generate() {
    const double samplingRate = 100;
    int sampleCount = static_cast<int>(samplingRate * duration);

    for(int i = 0; i < sampleCount; ++i) {
        double t = i / samplingRate;
        double value = amplitude * sin((2 * M_PI / term) * (t - startTime));
        data.push_back(value);
    }
}

void SinusoidalSignal::display() const {
    for(double d : data) {
        std::cout << d << std::endl;
    }
}

