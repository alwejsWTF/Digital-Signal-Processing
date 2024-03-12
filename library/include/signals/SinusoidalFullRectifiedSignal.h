#ifndef CYFROWEPRZETWARZANIESYGNALOW_SINUSOIDALFULLRECTIFIEDSIGNAL_H
#define CYFROWEPRZETWARZANIESYGNALOW_SINUSOIDALFULLRECTIFIEDSIGNAL_H

#include <ContinuousSignal.h>

class SinusoidalFullRectifiedSignal : public ContinuousSignal {
private:
    double term;

public:
    SinusoidalFullRectifiedSignal(double amplitude, double term, double startTime, double duration);

    double getTerm() const;
    void setTerm(double term);
};

#endif //CYFROWEPRZETWARZANIESYGNALOW_SINUSOIDALFULLRECTIFIEDSIGNAL_H
