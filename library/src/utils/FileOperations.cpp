#include "utils/FileOperations.h"
#include <iostream>
#include <fstream>

void FileOperations::save(const std::vector<double>& data, const std::string& fileName) {
    std::ofstream file(fileName, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Could not open file for writing: " << fileName << std::endl;
        return;
    }
    // file.write(reinterpret_cast<const char*>(&startTime), sizeof(startTime));
    // file.write(reinterpret_cast<const char*>(&samplingFreq), sizeof(samplingFreq));
    // file.write(reinterpret_cast<const char*>(&isComplex), sizeof(isComplex));
    // file.write(reinterpret_cast<const char*>(&numSamples), sizeof(numSamples));
    for (double value : data) {
        file.write(reinterpret_cast<const char*>(&value), sizeof(value));
    }
    file.close();
    std::cout << "Signal saved to file: " << fileName << std::endl;
}

std::vector<double> FileOperations::load(const std::string& fileName) {
    std::vector<double> data;
    std::ifstream file(fileName, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Could not open file for reading: " << fileName << std::endl;
        return data;
    }

    double value;
    while (file.read(reinterpret_cast<char*>(&value), sizeof(value))) {
        data.push_back(value);
    }
    file.close();
    std::cout << "Signal load from file: " << fileName << std::endl;
    return data;
}

