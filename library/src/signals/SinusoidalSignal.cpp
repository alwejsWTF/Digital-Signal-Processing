#include "signals/SinusoidalSignal.h"
#include <iostream>
#include <cmath>

SinusoidalSignal::SinusoidalSignal(double amplitude, double term, double startTime, double duration) :
amplitude(amplitude), term(term), startTime(startTime), duration(duration) {}

void SinusoidalSignal::generate() {
    constexpr double samplingRate = 100;
    const int sampleCount = static_cast<int>(samplingRate * duration);

    for(int i = 0; i < sampleCount; ++i) {
        const double t = i / samplingRate;
        double value = amplitude * sin((2 * M_PI / term) * (t - startTime));
        data.push_back(value);
    }
}

void SinusoidalSignal::display() const {
    for(const double d : data) {
        std::cout << d << std::endl;
    }
}

std::vector<double> SinusoidalSignal::getData() const {
    return data;
}

double SinusoidalSignal::getAmplitude() const {
    return amplitude;
}

double SinusoidalSignal::getTerm() const {
    return term;
}

double SinusoidalSignal::getStartTime() const {
    return startTime;
}

double SinusoidalSignal::getDuration() const {
    return duration;
}

void SinusoidalSignal::setData(const std::vector<double> &data) {
    this->data = data;
}

void SinusoidalSignal::setAmplitude(const double amplitude) {
    this->amplitude = amplitude;
}

void SinusoidalSignal::setTerm(const double term) {
    this->term = term;
}

void SinusoidalSignal::setStartTime(const double startTime) {
    this->startTime = startTime;
}

void SinusoidalSignal::setDuration(const double duration) {
    this->duration = duration;
}

