#ifndef CYFROWEPRZETWARZANIESYGNALOW_TRIANGULARSIGNAL_H
#define CYFROWEPRZETWARZANIESYGNALOW_TRIANGULARSIGNAL_H

#include <ContinuousSignal.h>

class TriangularSignal : public ContinuousSignal {
private:
    double term;
    double dutyCycle; // kw

public:
    TriangularSignal(double amplitude, double term, double dutyCycle, double startTime, double duration, double samplingRate);
    std::string getSignalName() override;

    double getTerm() const override;

    double getDutyCycle() const override;

    std::string getSignalType() override;
};

#endif //CYFROWEPRZETWARZANIESYGNALOW_TRIANGULARSIGNAL_H
