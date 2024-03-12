#ifndef CYFROWEPRZETWARZANIESYGNALOW_RECTANGULARSYMMETRICSIGNAL_H
#define CYFROWEPRZETWARZANIESYGNALOW_RECTANGULARSYMMETRICSIGNAL_H

#include "ContinuousSignal.h"

class RectangularSymmetricSignal : public ContinuousSignal {
private:
    double amplitude;
    double term;
    double dutyCycle; // kw

public:
    RectangularSymmetricSignal(double amplitude, double term, double dutyCycle, double startTime, double duration);
};

#endif //CYFROWEPRZETWARZANIESYGNALOW_RECTANGULARSYMMETRICSIGNAL_H
