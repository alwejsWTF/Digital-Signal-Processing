#ifndef CYFROWEPRZETWARZANIESYGNALOW_GAUSSIANNOISE_H
#define CYFROWEPRZETWARZANIESYGNALOW_GAUSSIANNOISE_H

#include <ContinuousSignal.h>

class GaussianNoise : public ContinuousSignal {
public:
    GaussianNoise(double amplitude, double startTime, double duration);
    void generate(double samplingRate) override;
};

#endif //CYFROWEPRZETWARZANIESYGNALOW_GAUSSIANNOISE_H
