#include "Signal.h"
#include <cmath>
#include <iostream>

Signal::Signal(double amplitude, double startTime, double duration, const std::function<double(double)> &func) :
amplitude(amplitude), startTime(startTime), duration(duration), signalFunction(func) {}

void Signal::generate(double const samplingRate) {
    data.clear();
    time.clear();
    double A_max;
    const int sampleCount = static_cast<int>(samplingRate * duration);
    for (int i = 0; i < sampleCount; ++i) {
        const double t = i / samplingRate + startTime;
        const double y = signalFunction(t);
        if (i != 0) {
            if (A_max < fabs(y)) A_max = fabs(y);
        } else A_max = fabs(y);
        time.push_back(t);
        data.push_back(y);
    }
    setAmplitude(A_max);
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

void Signal::setAmplitude(const double amplitude) {
    this->amplitude = amplitude;
}

void Signal::setStartTime(double const startTime) {
    this->startTime = startTime;
}

void Signal::setDuration(double const duration) {
    this->duration = duration;
}
