#ifndef CYFROWEPRZETWARZANIESYGNALOW_UNITIMPULSESIGNAL_H
#define CYFROWEPRZETWARZANIESYGNALOW_UNITIMPULSESIGNAL_H

#include <DiscreteSignal.h>

class UnitImpulseSignal : public DiscreteSignal {
private:
    int stepSampleNumber;
    int firstSample;
public:
    UnitImpulseSignal(double amplitude, double startTime, double duration, double samplingRate, int stepSampleNumber, int firstSample);
    void generate() override;
    std::string getSignalName() override;

    int getStepSampleNumber() const;

    int getFirstSample() const;
};

#endif //CYFROWEPRZETWARZANIESYGNALOW_UNITIMPULSESIGNAL_H
