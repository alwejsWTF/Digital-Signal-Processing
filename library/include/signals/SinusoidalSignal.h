#ifndef CYFROWEPRZETWARZANIESYGNALOW_SINUSOIDALSIGNAL_H
#define CYFROWEPRZETWARZANIESYGNALOW_SINUSOIDALSIGNAL_H

#include "ContinuousSignal.h"

class SinusoidalSignal : public ContinuousSignal {
private:
    double amplitude;
    double term;
public:
    SinusoidalSignal(double amplitude, double term, double startTime, double duration);
    ~SinusoidalSignal() override = default;

    void generate() override;

    double getAmplitude() const;
    double getTerm() const;

    void setAmplitude(double amplitude);
    void setTerm(double term);
};

#endif //CYFROWEPRZETWARZANIESYGNALOW_SINUSOIDALSIGNAL_H
