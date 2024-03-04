#include "Signal.h"
#include <iostream>

Signal::Signal(double startTime, double duration, const std::function<double(double)> &func) :
startTime(startTime), duration(duration), signalFunction(func) {}

void Signal::display() const {
    for(const double d : data) {
        std::cout << d << std::endl;
    }
}

std::vector<double> Signal::getData() const {
    return data;
}

void Signal::setData(const std::vector<double> &data) {
    this->data = data;
}

double Signal::getStartTime() const {
    return startTime;
}

double Signal::getDuration() const {
    return duration;
}

void Signal::setStartTime(double const startTime) {
    this->startTime = startTime;
}

void Signal::setDuration(double const duration) {
    this->duration = duration;
}