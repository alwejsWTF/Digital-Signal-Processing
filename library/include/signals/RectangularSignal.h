#ifndef CYFROWEPRZETWARZANIESYGNALOW_RECTANGULARSIGNAL_H
#define CYFROWEPRZETWARZANIESYGNALOW_RECTANGULARSIGNAL_H

#include "ContinuousSignal.h"

class RectangularSignal : public ContinuousSignal {
private:
    double amplitude;
    double term;
    double dutyCycle; // kw

public:
    RectangularSignal(double amplitude, double term, double dutyCycle, double startTime, double duration);
    ~RectangularSignal() override = default;

    void generate() override;
};
#endif //CYFROWEPRZETWARZANIESYGNALOW_RECTANGULARSIGNAL_H
