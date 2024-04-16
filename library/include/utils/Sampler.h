#ifndef CYFROWEPRZETWARZANIESYGNALOW_SAMPLER_H
#define CYFROWEPRZETWARZANIESYGNALOW_SAMPLER_H


#include <vector>

class Sampler {
public:
    static std::pair<std::vector<double>, std::vector<double>> uniformSample(const std::vector<double>& times, const std::vector<double>& samples, double samplingRate);
};


#endif //CYFROWEPRZETWARZANIESYGNALOW_SAMPLER_H
