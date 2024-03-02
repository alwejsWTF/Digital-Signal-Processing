#include "utils/SignalOperations.h"

std::vector<double> SignalOperations::add(const std::vector<double>& signalA, const std::vector<double>& signalB) {
    std::size_t size = std::min(signalA.size(), signalB.size());
    std::vector<double> result(size);

    for (std::size_t i = 0; i < size; ++i) {
        result[i] = signalA[i] + signalB[i];
    }

    return result;
}

std::vector<double> SignalOperations::subtract(const std::vector<double> &signalA, const std::vector<double> &signalB) {
    return std::vector<double>();
}

std::vector<double> SignalOperations::multiply(const std::vector<double> &signalA, const std::vector<double> &signalB) {
    return std::vector<double>();
}

std::vector<double> SignalOperations::divide(const std::vector<double> &signalA, const std::vector<double> &signalB) {
    return std::vector<double>();
}

