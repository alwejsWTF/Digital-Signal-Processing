#ifndef CYFROWEPRZETWARZANIESYGNALOW_SINUSOIDALSIGNAL_H
#define CYFROWEPRZETWARZANIESYGNALOW_SINUSOIDALSIGNAL_H

#include "ContinuousSignal.h"

class SinusoidalSignal : public ContinuousSignal {
private:
    double term;
public:
    SinusoidalSignal(double amplitude, double term, double startTime, double duration, double samplingRate);
    std::string getSignalName() override;

    double getTerm() const override;
    void setTerm(double term);

    std::string getSignalType() override;
};

#endif //CYFROWEPRZETWARZANIESYGNALOW_SINUSOIDALSIGNAL_H
