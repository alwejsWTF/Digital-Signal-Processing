#include "utils/sensor.h"
#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <random>
#include <algorithm>
#include "utils/crossCorrelation.h"

Sensor::Sensor(SignalPtr signal, double term, double propagationSpeed)
        : signal(signal), term(term), propagationSpeed(propagationSpeed) {
    transmittedSignal = signal->getData();
    timeVector = signal->getTime();
    int bufferLength = transmittedSignal.size();
    receivedSignal.resize(bufferLength);
}

double Sensor::simulateEchoAndCalculateDistance(double objectDistance, double objectSpeed) {
    double delay = 2 * objectDistance / (propagationSpeed + objectSpeed);  // Delay in seconds (signal there and back)
    int delay_samples = static_cast<int>(signal->getSamplingRate() * delay);

    // Generate received signal with echo
    receivedSignal.resize(transmittedSignal.size());
    if (delay_samples < receivedSignal.size()) {
        for (int i = 0; i < receivedSignal.size() - delay_samples; ++i) {
            receivedSignal[i + delay_samples] = transmittedSignal[i];
        }
    }

    // Perform cross-correlation
    std::vector<double> timeVectorTMP(2 * receivedSignal.size() - 1);
    std::vector<double> correlation(2 * receivedSignal.size() - 1);
    for (int i = 0; i < correlation.size(); ++i) {
        timeVectorTMP[i] = static_cast<double>(i - (receivedSignal.size() - 1)) / signal->getSamplingRate();
        double sum = 0.0;
        for (int j = 0; j < transmittedSignal.size(); ++j) {
            int shiftedIndex = (j + i) % transmittedSignal.size();
            sum += transmittedSignal[j] * receivedSignal[shiftedIndex];
        }
        correlation[i] = sum;
    }
    this->timeVectorCross = timeVectorTMP;
    this->crossCorrelation = correlation;

    std::vector<double> timeVectorTMPforPlot;
    std::vector<double> correlationforPlot;
    std::tie(correlationforPlot, timeVectorTMPforPlot) = directCrossCorrelation(transmittedSignal, 1.0 / signal->getSamplingRate(),
                                                          receivedSignal, 1.0 / signal->getSamplingRate());
    this->timeVectorCrossPlot = timeVectorTMPforPlot;
    this->crossCorrelationPlot = correlationforPlot;

    // Find the index of the maximum value in the correlation
    int maxIndex = std::max_element(correlation.begin(), correlation.end()) - correlation.begin();

    // Calculate the time delay based on the maximum index and sampling frequency
    double timeDelay = maxIndex / signal->getSamplingRate();

    // Calculate the object distance using the speed of sound
    double calculatedDistance = timeDelay * propagationSpeed / 2.0;

    // Update the object distance
    return calculatedDistance;
}


std::vector<double> Sensor::getTransmitted() const {
    return transmittedSignal;
}

std::vector<double> Sensor::getReceived() const {
    return receivedSignal;
}

std::vector<double> Sensor::getCrossCorrelation() const {
    return crossCorrelation;
}

std::vector<double> Sensor::getTimeVector() const {
    return timeVector;
}

std::vector<double> Sensor::getTimeVectorCross() const {
    return timeVectorCross;
}

std::vector<double> Sensor::getTimeVectorCrossPlot() const {
    return timeVectorCrossPlot;
}

std::vector<double> Sensor::getCrossCorrelationPlot()  const {
    return crossCorrelationPlot;
}
