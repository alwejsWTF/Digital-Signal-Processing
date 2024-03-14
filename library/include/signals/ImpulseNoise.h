#ifndef CYFROWEPRZETWARZANIESYGNALOW_IMPULSENOISE_H
#define CYFROWEPRZETWARZANIESYGNALOW_IMPULSENOISE_H

#include <DiscreteSignal.h>

class ImpulseNoise : public DiscreteSignal {
private:
    double probability;
public:
    ImpulseNoise(double amplitude, double startTime, double duration, double probability);
    void generate(double samplingRate) override;
    std::string getSignalName() override;
};

#endif //CYFROWEPRZETWARZANIESYGNALOW_IMPULSENOISE_H
