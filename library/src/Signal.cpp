#include "Signal.h"
#include <cmath>
#include <utility>
#include <sstream>

Signal::Signal(double amplitude, double startTime, double duration, double samplingRate, const std::function<double(double)> &func) :
amplitude(amplitude), startTime(startTime), duration(duration), samplingRate(samplingRate), signalFunction(func) {}

Signal::Signal(std::vector<double> data, std::vector<double> time, double startTime, double duration, double samplingRate)
: data(std::move(data)), time(std::move(time)), startTime(startTime), samplingRate(samplingRate) {}

void Signal::generate() {
    data.clear();
    time.clear();
    const int sampleCount = static_cast<int>(samplingRate * duration);
    for (int i = 0; i < sampleCount; ++i) {
        const double t = i / samplingRate + startTime;
        time.push_back(t);
        data.push_back(signalFunction(t));
    }
}

std::string Signal::display() {
    std::stringstream chain;
    chain << "Wygenerownany sygnal:";
    int i = 0;
    for(const double d : data) {
        if (i % 5 == 0) chain << "\n";
        chain << d << ", ";
        i++;
    }
    return chain.str();
}

std::string Signal::getSignalName() {
    std::stringstream chain;
    chain << "Sygnal";
    return chain.str();
}

std::string Signal::getSignalType() {
    std::stringstream chain;
    return chain.str();
}


std::vector<double> Signal::getTime() const {
    return time;
}

double Signal::meanValue() {
    double sum = 0;
    for (double & i : data) sum += i;
    return sum / static_cast<double>(data.size());
}

double Signal::meanAbsoluteValue() {
    double sum = 0;
    for (double & i : data) sum += std::abs(i);
    return sum / static_cast<double>(data.size());
}

double Signal::meanPower() {
    double squareSum = 0;
    for (double & i : data) squareSum += i * i;
    return squareSum / static_cast<double>(data.size());
}

double Signal::variance() {
    double mean = meanValue();
    double sqSum = 0;
    for (double & i : data) sqSum += (i - mean) * (i - mean);
    return sqSum / static_cast<double>(data.size());
}

double Signal::rootMeanSquare() {
    return std::sqrt(meanPower());
}

std::vector<double> Signal::getData() const {
    return data;
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

double Signal::getSamplingRate() const {
    return samplingRate;
}

double Signal::getMaxAmplitude() {
    auto comp = [](double a, double b) {
        return std::abs(a) < std::abs(b);
    };
    auto max_it = std::max_element(data.begin(), data.end(), comp);
    return std::abs(*max_it);
}

void Signal::setData(std::vector<double> data) {
    this->data = std::move(data);
}

void Signal::setTime(std::vector<double> time) {
    this->time = std::move(time);
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

void Signal::setSamplingRate(double const samplingRate) {
    this->samplingRate = samplingRate;
}

