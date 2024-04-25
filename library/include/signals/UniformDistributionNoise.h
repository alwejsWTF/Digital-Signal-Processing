#ifndef CYFROWEPRZETWARZANIESYGNALOW_UNIFORMDISTRIBUTIONNOISE_H
#define CYFROWEPRZETWARZANIESYGNALOW_UNIFORMDISTRIBUTIONNOISE_H

#include <ContinuousSignal.h>

class UniformDistributionNoise : public ContinuousSignal {
public:
    UniformDistributionNoise(double amplitude, double startTime, double duration, double samplingRate);
    void generate() override;
    std::string getSignalName() override;

    std::string getSignalType() override;
};

#endif //CYFROWEPRZETWARZANIESYGNALOW_UNIFORMDISTRIBUTIONNOISE_H
