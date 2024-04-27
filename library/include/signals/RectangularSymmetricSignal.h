#ifndef CYFROWEPRZETWARZANIESYGNALOW_RECTANGULARSYMMETRICSIGNAL_H
#define CYFROWEPRZETWARZANIESYGNALOW_RECTANGULARSYMMETRICSIGNAL_H

#include "ContinuousSignal.h"

class RectangularSymmetricSignal : public ContinuousSignal {
private:
    double term;
    double dutyCycle; // kw

public:
    RectangularSymmetricSignal(double amplitude, double term, double dutyCycle, double startTime, double duration, double samplingRate);
    std::string getSignalName() override;

    double getTerm() const;

    double getDutyCycle() const;
};

#endif //CYFROWEPRZETWARZANIESYGNALOW_RECTANGULARSYMMETRICSIGNAL_H
