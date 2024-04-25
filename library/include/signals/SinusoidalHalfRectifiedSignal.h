#ifndef CYFROWEPRZETWARZANIESYGNALOW_SINUSOIDALHALFRECTIFIEDSIGNAL_H
#define CYFROWEPRZETWARZANIESYGNALOW_SINUSOIDALHALFRECTIFIEDSIGNAL_H

#include <ContinuousSignal.h>

class SinusoidalHalfRectifiedSignal : public ContinuousSignal {
private:
    double term;

public:
    SinusoidalHalfRectifiedSignal(double amplitude, double term, double startTime, double duration, double samplingRate);
    std::string getSignalName() override;

    double getTerm() const override;
    void setTerm(double term);

    std::string getSignalType() override;
};


#endif //CYFROWEPRZETWARZANIESYGNALOW_SINUSOIDALHALFRECTIFIEDSIGNAL_H
