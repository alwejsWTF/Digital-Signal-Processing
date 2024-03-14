#ifndef CYFROWEPRZETWARZANIESYGNALOW_UNITIMPULSESIGNAL_H
#define CYFROWEPRZETWARZANIESYGNALOW_UNITIMPULSESIGNAL_H

#include <DiscreteSignal.h>

class UnitImpulseSignal : public DiscreteSignal {
private:
    int stepSampleNumber;
    int firstSample;
public:
    UnitImpulseSignal(double amplitude, double startTime, double duration, int stepSampleNumber, int firstSample);
    void generate(double samplingRate) override;
    std::string getSignalName() override;
};

#endif //CYFROWEPRZETWARZANIESYGNALOW_UNITIMPULSESIGNAL_H
