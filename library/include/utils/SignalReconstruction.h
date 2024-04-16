#ifndef CYFROWEPRZETWARZANIESYGNALOW_SIGNALRECONSTRUCTION_H
#define CYFROWEPRZETWARZANIESYGNALOW_SIGNALRECONSTRUCTION_H


#include <vector>
#include <cmath>

class SignalReconstruction {
public:
    static std::pair<std::vector<double>, std::vector<double>> zeroOrderHold(const std::vector<int>& quantizedSamples, const std::vector<double>& times);
    static std::pair<std::vector<double>, std::vector<double>> firstOrderHold(const std::vector<int>& quantizedSamples, const std::vector<double>& times);
    static std::vector<double> sincInterpolation(const std::vector<int>& quantizedSamples, double samplingRate);
    static double sinc(double t);
};


#endif //CYFROWEPRZETWARZANIESYGNALOW_SIGNALRECONSTRUCTION_H
