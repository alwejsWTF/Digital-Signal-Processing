#include "utils/FileOperations.h"
#include <fstream>
#include <iostream>

void FileOperations::saveSignalData(const std::vector<double>& data, const std::string& fileName) {
    std::ofstream file(fileName, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Could not open file for writing: " << fileName << std::endl;
        return;
    }

    for (double value : data) {
        file.write(reinterpret_cast<const char*>(&value), sizeof(value));
    }
    file.close();
}

std::vector<double> FileOperations::loadSignalData(const std::string& fileName) {
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
    return data;
}
