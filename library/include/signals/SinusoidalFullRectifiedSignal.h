#ifndef CYFROWEPRZETWARZANIESYGNALOW_SINUSOIDALFULLRECTIFIEDSIGNAL_H
#define CYFROWEPRZETWARZANIESYGNALOW_SINUSOIDALFULLRECTIFIEDSIGNAL_H

#include <ContinuousSignal.h>

class SinusoidalFullRectifiedSignal : public ContinuousSignal {
private:
    double term;

public:
    SinusoidalFullRectifiedSignal(double amplitude, double term, double startTime, double duration, double samplingRate);
    std::string getSignalName() override;

    double getTerm() const override;
    void setTerm(double term);

    std::string getSignalType() override;
};

#endif //CYFROWEPRZETWARZANIESYGNALOW_SINUSOIDALFULLRECTIFIEDSIGNAL_H
