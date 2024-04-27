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

    double getTerm() const;

    double getDutyCycle() const;
};

#endif //CYFROWEPRZETWARZANIESYGNALOW_TRIANGULARSIGNAL_H
