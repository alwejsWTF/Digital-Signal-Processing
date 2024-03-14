#ifndef CYFROWEPRZETWARZANIESYGNALOW_GAUSSIANNOISE_H
#define CYFROWEPRZETWARZANIESYGNALOW_GAUSSIANNOISE_H

#include <ContinuousSignal.h>

class GaussianNoise : public ContinuousSignal {
public:
    GaussianNoise(double amplitude, double startTime, double duration, double samplingRate);
    void generate() override;
    std::string getSignalName() override;
};

#endif //CYFROWEPRZETWARZANIESYGNALOW_GAUSSIANNOISE_H
