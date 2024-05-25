#include "utils/sensor.h"
#include <iostream>
#include <cmath>
#include <algorithm>

Sensor::Sensor(double signalPeriod, double samplingFrequency, int bufferLength, double reportPeriod)
        : signalPeriod(signalPeriod), samplingFrequency(samplingFrequency), bufferLength(bufferLength), reportPeriod(reportPeriod) {
    numSamples = static_cast<int>(samplingFrequency * signalPeriod);
    transmittedSignal.resize(bufferLength);
    receivedSignal.resize(bufferLength);
}

void Sensor::generateSignal() {
    for (int i = 0; i < bufferLength; ++i) {
        transmittedSignal[i] = sin(2 * M_PI * i / numSamples) + 0.5 * sin(4 * M_PI * i / numSamples);
    }
}

void Sensor::simulateEcho(double objectDistance, double objectSpeed, double propagationSpeed) {
    this->objectDistance = objectDistance;
    this->objectSpeed = objectSpeed;
    this->propagationSpeed = propagationSpeed;

    double timeDelay = 2 * objectDistance / propagationSpeed;
    int sampleDelay = static_cast<int>(timeDelay * samplingFrequency);

    for (int i = 0; i < bufferLength; ++i) {
        if (i < sampleDelay) {
            receivedSignal[i] = 0;
        } else {
            receivedSignal[i] = transmittedSignal[i - sampleDelay];
        }
    }
}

void Sensor::performCrossCorrelation() {
    int corrSize = bufferLength + bufferLength - 1;
    crossCorrelation.resize(corrSize, 0.0);

    for (int n = 0; n < corrSize; ++n) {
        for (int k = 0; k < bufferLength; ++k) {
            if (n - k >= 0 && n - k < bufferLength) {
                crossCorrelation[n] += transmittedSignal[k] * receivedSignal[n - k];
            }
        }
    }
}

double Sensor::calculateDistance() {
    auto maxIt = std::max_element(crossCorrelation.begin(), crossCorrelation.end());
    int maxIndex = std::distance(crossCorrelation.begin(), maxIt);
    double timeDelay = (maxIndex - bufferLength + 1) / samplingFrequency;
    return (propagationSpeed * timeDelay) / 2;
}