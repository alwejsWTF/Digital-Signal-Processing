#ifndef CYFROWEPRZETWARZANIESYGNALOW_SINUSOIDALSIGNAL_H
#define CYFROWEPRZETWARZANIESYGNALOW_SINUSOIDALSIGNAL_H

#include "ContinuousSignal.h"

class SinusoidalSignal : public ContinuousSignal {
private:
    double term;
public:
    SinusoidalSignal(double amplitude, double term, double startTime, double duration);

    double getTerm() const;
    void setTerm(double term);
};

#endif //CYFROWEPRZETWARZANIESYGNALOW_SINUSOIDALSIGNAL_H
