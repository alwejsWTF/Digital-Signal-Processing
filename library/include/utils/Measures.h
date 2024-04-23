#ifndef CYFROWEPRZETWARZANIESYGNALOW_MEASURES_H
#define CYFROWEPRZETWARZANIESYGNALOW_MEASURES_H


#include <vector>

class Measures {
public:
    static double meanSquaredError(const std::vector<double>& original, const std::vector<double>& reconstructed);
    static double signalToNoiseRatio(const std::vector<double>& original, const std::vector<double>& reconstructed);
    static double peakSignalToNoiseRatio(const std::vector<double>& original, const std::vector<double>& reconstructed);
    static double maximumDifference(const std::vector<double>& original, const std::vector<double>& reconstructed);
    static double enob(const std::vector<double>& original, const std::vector<double>& reconstructed);
};


#endif //CYFROWEPRZETWARZANIESYGNALOW_MEASURES_H
