#ifndef CYFROWEPRZETWARZANIESYGNALOW_UNIFORMDISTRIBUTIONNOISE_H
#define CYFROWEPRZETWARZANIESYGNALOW_UNIFORMDISTRIBUTIONNOISE_H

#include <ContinuousSignal.h>

class UniformDistributionNoise : public ContinuousSignal {
public:
    UniformDistributionNoise(double amplitude, double startTime, double duration);
    void generate(double samplingRate) override;
    std::string getSignalName() override;
};

#endif //CYFROWEPRZETWARZANIESYGNALOW_UNIFORMDISTRIBUTIONNOISE_H
