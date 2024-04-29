#include "utils/FileOperations.h"
#include <iostream>
#include <fstream>
#include <conio.h>
#include <allSignals.h>
#include <nlohmann/json.hpp>


void showFileInfo(const double startTime, const double samplingRate, const bool isComplex, const int dataSize, const std::string& display) {
    int choice = 0;
    std::cout << "Show file info?\n"
              << "1. Yes.\n"
              << "2. No.\n"
              << "Choice: ";
    std::cin >> choice;
    if (choice == 1) {
        std::cout << "=================FILE INFO=================\n"
                  << "Start time (t1): " << startTime
                  << "\nSampling rate: " << samplingRate
                  << "\nIs complex: " << isComplex
                  << "\nData size: " << dataSize
                  << std::endl << display << std::endl
                  << "Press any key to continue...\n";
        _getch();
    }
}

void FileOperations::save(const SignalPtr& signal, const std::string& fileName) {
    std::ofstream file(fileName, std::ios::binary);
    if (!file.is_open()) {
        std::cout << "Could not open file for writing: " << fileName << std::endl;
        return;
    }
    std::vector<double> data = signal->getData();
    double startTime = signal->getStartTime();
    double samplingRate = signal->getSamplingRate();
    bool isComplex = false;
    int dataSize = static_cast<int>(data.size());

    std::string name = signal->getSignalName();
    int nameSize = static_cast<int>(name.size());
    file.write(reinterpret_cast<const char*>(&nameSize), sizeof(nameSize));
    file.write(name.c_str(), nameSize);

    file.write(reinterpret_cast<const char*>(&startTime), sizeof(startTime));
    file.write(reinterpret_cast<const char*>(&samplingRate), sizeof(samplingRate));
    file.write(reinterpret_cast<const char*>(&isComplex), sizeof(isComplex));
    file.write(reinterpret_cast<const char*>(&dataSize), sizeof(dataSize));
    if (name == "Sygnal sinusoidalny" || name == "Sygnal sinusoidalny wyprostowany jednopolowkowo" ||
        name == "Sygnal sinusoidalny wyprostowany dwupolowkowo" || name == "Sygnal prostokatny" ||
        name == "Sygnal prostokatny symetryczny" || name == "Sygnal trojkatny") {
        auto tmpSignal = std::dynamic_pointer_cast<SinusoidalSignal>(signal);
        double term = tmpSignal->getTerm();
        file.write(reinterpret_cast<const char*>(&term), sizeof(term));
    }
    if (name == "Sygnal prostokatny" || name == "Sygnal prostokatny symetryczny" || name == "Sygnal trojkatny") {
        auto tmpSignal = std::dynamic_pointer_cast<RectangularSignal>(signal);
        double dutyCycle = tmpSignal->getDutyCycle();
        file.write(reinterpret_cast<const char*>(&dutyCycle), sizeof(dutyCycle));
    }
    if (name == "Skok jednostkowy") {
        auto tmpSignal = std::dynamic_pointer_cast<UnitStepSignal>(signal);
        double stepTime = tmpSignal->getStepTime();
        file.write(reinterpret_cast<const char*>(&stepTime), sizeof(stepTime));
    }
    if (name == "Impuls jednostkowy") {
        auto tmpSignal = std::dynamic_pointer_cast<UnitImpulseSignal>(signal);
        double stepSampleNumber = tmpSignal->getStepSampleNumber();
        double firstSample = tmpSignal->getFirstSample();
        file.write(reinterpret_cast<const char*>(&stepSampleNumber), sizeof(stepSampleNumber));
        file.write(reinterpret_cast<const char*>(&firstSample), sizeof(firstSample));
    }
    if (name == "Szum impulsowy") {
        auto tmpSignal = std::dynamic_pointer_cast<ImpulseNoise>(signal);
        double probability = tmpSignal->getProbability();
        file.write(reinterpret_cast<const char*>(&probability), sizeof(probability));
    }
    for (double value : data) {
        file.write(reinterpret_cast<const char*>(&value), sizeof(value));
    }
    file.close();
    std::cout << "Signal saved to file: " << fileName << std::endl;
}

std::pair<SignalPtr, nlohmann::json> FileOperations::load(const std::string& fileName) {
    SignalPtr signal = nullptr;
    std::vector<double> data;
    std::ifstream file(fileName, std::ios::binary);
    if (!file.is_open()) {
        std::cout << "Could not open file for reading: " << fileName << std::endl;
        return {signal, std::string()};
    }
    double value;
    double startTime;
    double samplingRate;
    bool isComplex;
    int dataSize;

    nlohmann::json j = nlohmann::json::object();
    j["name"] = NULL;
    j["term"] = NULL;
    j["dutyCycle"] = NULL;
    j["stepTime"] = NULL;
    j["stepSampleNumber"] = NULL;
    j["firstSample"] = NULL;
    j["probability"] = NULL;

    int nameSize;
    file.read(reinterpret_cast<char*>(&nameSize), sizeof(nameSize));
    char* nameBuffer = new char[nameSize + 1];
    file.read(nameBuffer, nameSize);
    nameBuffer[nameSize] = '\0';
    std::string name(nameBuffer);
    delete[] nameBuffer;
    j["name"] = name;
//    return j.dump();

    file.read(reinterpret_cast<char*>(&startTime), sizeof(startTime));
    file.read(reinterpret_cast<char*>(&samplingRate), sizeof(samplingRate));
    file.read(reinterpret_cast<char*>(&isComplex), sizeof(isComplex));
    file.read(reinterpret_cast<char*>(&dataSize), sizeof(dataSize));
    if (name == "Sygnal sinusoidalny" || name == "Sygnal sinusoidalny wyprostowany jednopolowkowo" ||
        name == "Sygnal sinusoidalny wyprostowany dwupolowkowo" || name == "Sygnal prostokatny" ||
        name == "Sygnal prostokatny symetryczny" || name == "Sygnal trojkatny") {
        double term;
        file.read(reinterpret_cast<char*>(&term), sizeof(term));
        j["term"] = term;
    }
    if (name == "Sygnal prostokatny" || name == "Sygnal prostokatny symetryczny" || name == "Sygnal trojkatny") {
        double dutyCycle;
        file.read(reinterpret_cast<char*>(&dutyCycle), sizeof(dutyCycle));
        j["dutyCycle"] = dutyCycle;
    }
    if (name == "Skok jednostkowy") {
        double stepTime;
        file.read(reinterpret_cast<char*>(&stepTime), sizeof(stepTime));
        j["stepTime"] = stepTime;
    }
    if (name == "Impuls jednostkowy") {
        double stepSampleNumber;
        double firstSample;
        file.read(reinterpret_cast<char*>(&stepSampleNumber), sizeof(stepSampleNumber));
        file.read(reinterpret_cast<char*>(&firstSample), sizeof(firstSample));
        j["stepSampleNumber"] = stepSampleNumber;
        j["firstSample"] = firstSample;
    }
    if (name == "Szum impulsowy") {
        double probability;
        file.read(reinterpret_cast<char*>(&probability), sizeof(probability));
        j["probability"] = probability;
    }
    while (file.read(reinterpret_cast<char*>(&value), sizeof(value))) {
        data.push_back(value);
    }
    file.close();

    double duration = dataSize / samplingRate;
    double interval = 1.0 / samplingRate;
    std::vector<double> time;
    for (int i = 0; i < dataSize; ++i)
        time.push_back(startTime + interval * i);

    signal = std::make_shared<Signal>(data, time, startTime, duration, samplingRate);
    signal->setAmplitude(signal->getMaxAmplitude());

    std::cout << "Signal load from file: " << fileName << std::endl;
    showFileInfo(startTime, samplingRate, isComplex, dataSize, signal->display());
    return {signal, j};
}
