#ifndef CYFROWEPRZETWARZANIESYGNALOW_SINUSOIDALFULLRECTIFIEDSIGNAL_H
#define CYFROWEPRZETWARZANIESYGNALOW_SINUSOIDALFULLRECTIFIEDSIGNAL_H

#include <ContinuousSignal.h>

class SinusoidalFullRectifiedSignal : public ContinuousSignal {
private:
    double amplitude;
    double term;

public:
    SinusoidalFullRectifiedSignal(double amplitude, double term, double startTime, double duration);

    void generate() override;

    double getAmplitude() const;
    double getTerm() const;

    void setAmplitude(double amplitude);
    void setTerm(double term);
};

#endif //CYFROWEPRZETWARZANIESYGNALOW_SINUSOIDALFULLRECTIFIEDSIGNAL_H
