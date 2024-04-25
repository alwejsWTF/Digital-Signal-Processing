#ifndef CYFROWEPRZETWARZANIESYGNALOW_IMPULSENOISE_H
#define CYFROWEPRZETWARZANIESYGNALOW_IMPULSENOISE_H

#include <DiscreteSignal.h>

class ImpulseNoise : public DiscreteSignal {
private:
    double probability;
public:
    ImpulseNoise(double amplitude, double startTime, double duration, double samplingRate, double probability);
    void generate() override;
    std::string getSignalName() override;

    double getProbability() const;

    std::string getSignalType() override;
};

#endif //CYFROWEPRZETWARZANIESYGNALOW_IMPULSENOISE_H
