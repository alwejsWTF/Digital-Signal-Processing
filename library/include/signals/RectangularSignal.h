#ifndef CYFROWEPRZETWARZANIESYGNALOW_RECTANGULARSIGNAL_H
#define CYFROWEPRZETWARZANIESYGNALOW_RECTANGULARSIGNAL_H

#include "ContinuousSignal.h"

class RectangularSignal : public ContinuousSignal {
private:
    double term;
    double dutyCycle; // kw

public:
    RectangularSignal(double amplitude, double term, double dutyCycle, double startTime, double duration, double samplingRate);
    std::string getSignalName() override;

    double getTerm() const;

    double getDutyCycle() const;

    void setTerm(double term);

    void setDutyCycle(double dutyCycle);
};
#endif //CYFROWEPRZETWARZANIESYGNALOW_RECTANGULARSIGNAL_H
