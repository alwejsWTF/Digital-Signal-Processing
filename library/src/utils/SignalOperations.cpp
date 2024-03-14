#include "utils/SignalOperations.h"
#include <algorithm>
#include <cmath>
#include <stdexcept>

std::vector<double> SignalOperations::add(const std::vector<double>& signalA, const std::vector<double>& signalB) {
    if (signalA.size() != signalB.size()) throw std::invalid_argument("Vectors must be of equal size.");
    std::vector<double> result(signalA.size());
    std::transform(signalA.begin(), signalA.end(), signalB.begin(), result.begin(), std::plus<>());
    return result;
}

std::vector<double> SignalOperations::subtract(const std::vector<double> &signalA, const std::vector<double> &signalB) {
    if (signalA.size() != signalB.size()) throw std::invalid_argument("Vectors must be of equal size.");
    std::vector<double> result(signalA.size());
    std::transform(signalA.begin(), signalA.end(), signalB.begin(), result.begin(), std::minus<>());
    return result;
}

std::vector<double> SignalOperations::multiply(const std::vector<double> &signalA, const std::vector<double> &signalB) {
    if (signalA.size() != signalB.size()) throw std::invalid_argument("Vectors must be of equal size.");
    std::vector<double> result(signalA.size());
    std::transform(signalA.begin(), signalA.end(), signalB.begin(), result.begin(), std::multiplies<>());
    return result;
}

std::vector<double> SignalOperations::divide(const std::vector<double> &signalA, const std::vector<double> &signalB) {
    if (signalA.size() != signalB.size()) throw std::invalid_argument("Vectors must be of equal size.");
    std::vector<double> result(signalA.size());
    std::transform(signalA.begin(), signalA.end(), signalB.begin(), result.begin(), [](double const a, double const b) -> double {
        if (b == 0) return 0;
        return a / b;
    });
    return result;
}

