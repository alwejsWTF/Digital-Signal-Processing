#ifndef CYFROWEPRZETWARZANIESYGNALOW_SIGNALOPERATIONS_H
#define CYFROWEPRZETWARZANIESYGNALOW_SIGNALOPERATIONS_H

#include <vector>

class SignalOperations {
public:
    static std::vector<double> add(const std::vector<double>& signalA, const std::vector<double>& signalB);
    static std::vector<double> subtract(const std::vector<double>& signalA, const std::vector<double>& signalB);
    static std::vector<double> multiply(const std::vector<double>& signalA, const std::vector<double>& signalB);
    static std::vector<double> divide(const std::vector<double>& signalA, const std::vector<double>& signalB, int choice);
};

#endif //CYFROWEPRZETWARZANIESYGNALOW_SIGNALOPERATIONS_H
