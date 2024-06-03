#include "utils/sensor.h"
#include <iostream>
#include <cmath>
#include <algorithm>
#include "utils/crossCorrelation.h"

Sensor::Sensor(SignalPtr signal, double propagationSpeed)
        : signal(signal), propagationSpeed(propagationSpeed) {
    transmittedSignal = signal->getData();
    int bufferLength = transmittedSignal.size();
    receivedSignal.resize(bufferLength);
    std::cout << "Created Sensor object. Buffer length: " << bufferLength << std::endl;
}

void Sensor::simulateEcho(double objectDistance, double objectSpeed) {
    this->objectDistance = objectDistance;
    this->objectSpeed = objectSpeed;

    // Pobierz wymagane parametry
    double samplingFrequency = signal->getSamplingRate();
    double signalPeriod = signal->getDuration();
    int bufferLength = static_cast<int>(samplingFrequency * signalPeriod);

    // Zresetuj odbierany sygnał
    receivedSignal.clear();
    receivedSignal.resize(bufferLength, 0.0);

    // Oblicz opóźnienie czasowe i próbkowe
    double timeDelay = 2 * objectDistance / propagationSpeed;
    int sampleDelay = static_cast<int>(timeDelay * samplingFrequency);

    std::cout << "Echo simulation data:" << std::endl;
    std::cout << "Sample delay: " << sampleDelay << std::endl;
    std::cout << "Transmitted signal samples:" << std::endl;
    for (int i = 0; i < transmittedSignal.size(); ++i) {
        std::cout << transmittedSignal[i] << " ";
    }
    std::cout << std::endl;
    std::cout << "Received signal samples:" << std::endl;

    // Symuluj echo
    for (int i = 0; i < bufferLength; ++i) {
        if (i >= sampleDelay && (i - sampleDelay) < transmittedSignal.size()) {
            // Przesuń próbki sygnału o opóźnienie próbkowe i dodaj do odbieranego sygnału
            receivedSignal[i] = transmittedSignal[i - sampleDelay];
        }
        std::cout << receivedSignal[i] << " ";
    }
    std::cout << std::endl;
}



void Sensor::performCrossCorrelation() {
    double samplingFrequency = signal->getSamplingRate();
    double hDeltaT = 1.0 / samplingFrequency; // DeltaT dla sygnału wysyłanego
    double xDeltaT = 1.0 / samplingFrequency; // DeltaT dla sygnału odbieranego

    // Wywołujemy funkcję korelacji krzyżowej
    auto [crossCorrelation, timeVector] = directCrossCorrelation(transmittedSignal, hDeltaT, receivedSignal, xDeltaT);

    std::cout << "Cross correlation data:" << std::endl;
    std::cout << "Transmitted signal samples:" << std::endl;
    for (int i = 0; i < transmittedSignal.size(); ++i) {
        std::cout << transmittedSignal[i] << " ";
    }
    std::cout << std::endl;
    std::cout << "Received signal samples:" << std::endl;
    for (int i = 0; i < receivedSignal.size(); ++i) {
        std::cout << receivedSignal[i] << " ";
    }
    std::cout << std::endl;

    // Zapisujemy wyniki
    this->crossCorrelation = crossCorrelation;
    this->timeVectorCrossCorrelation = timeVector;
}


double Sensor::calculateDistance() {
    auto maxIt = std::max_element(crossCorrelation.begin(), crossCorrelation.end());
    int maxIndex = std::distance(crossCorrelation.begin(), maxIt);

    // Ensure that the maximum correlation index is within bounds
    if (maxIndex >= 0 && maxIndex < timeVectorCrossCorrelation.size()) {
        // Get the time delay from the cross-correlation time vector
        double timeDelay = timeVectorCrossCorrelation[maxIndex];

        // Calculate distance using the speed of sound and the time delay
        double distance = (propagationSpeed * timeDelay) / 2;

        // Print diagnostic information
        std::cout << "Max correlation index: " << maxIndex << std::endl;
        std::cout << "Calculated distance: " << distance << std::endl;

        return distance;
    } else {
        // Handle the case when the maximum correlation index is out of bounds
        std::cout << "Error: maxIndex out of range." << std::endl;
        return 0.0; // or other error handling mechanism
    }
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

std::vector<double> Sensor::getTimeVectorTransmitted() const {
    double samplingRate = signal->getSamplingRate();
    int numSamples = transmittedSignal.size();
    std::vector<double> timeVector(numSamples);
    for (int i = 0; i < numSamples; ++i) {
        timeVector[i] = i / samplingRate;
    }
    return timeVector;
}

std::vector<double> Sensor::getTimeVectorReceived() const {
    double samplingRate = signal->getSamplingRate();
    int numSamples = receivedSignal.size();
    std::vector<double> timeVector(numSamples);
    for (int i = 0; i < numSamples; ++i) {
        timeVector[i] = i / samplingRate;
    }
    return timeVector;
}

std::vector<double> Sensor::getTimeVectorCrossCorrelation() const {
    return timeVectorCrossCorrelation;
}