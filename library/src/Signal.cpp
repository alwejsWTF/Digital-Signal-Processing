#include "Signal.h"
#include <cmath>
#include <iostream>

Signal::Signal(double amplitude, double startTime, double duration, const std::function<double(double)> &func) :
amplitude(amplitude), startTime(startTime), duration(duration), signalFunction(func) {}

void Signal::generate(double const samplingRate) {
    data.clear();
    time.clear();
    const int sampleCount = static_cast<int>(samplingRate * duration);
    for (int i = 0; i < sampleCount; ++i) {
        const double t = i / samplingRate + startTime;
        time.push_back(t);
        data.push_back(signalFunction(t));
    }
}

void Signal::display() const {
    for(const double d : data) {
        std::cout << d << std::endl;
    }
}

std::vector<double> Signal::getData() const {
    return data;
}

std::vector<double> Signal::getTime() const {
    return time;
}

double Signal::getAmplitude() const {
    return amplitude;
}

double Signal::getStartTime() const {
    return startTime;
}

double Signal::getDuration() const {
    return duration;
}

double Signal::getMaxAmplitude() {
    auto comp = [](double a, double b) {
        return std::abs(a) < std::abs(b);
    };
    auto max_it = std::max_element(data.begin(), data.end(), comp);
    return std::abs(*max_it);
}

void Signal::setAmplitude(const double amplitude) {
    this->amplitude = amplitude;
}

void Signal::setStartTime(double const startTime) {
    this->startTime = startTime;
}

void Signal::setDuration(double const duration) {
    this->duration = duration;
}
