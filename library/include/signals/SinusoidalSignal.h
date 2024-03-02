#ifndef CYFROWEPRZETWARZANIESYGNALOW_SINUSOIDALSIGNAL_H
#define CYFROWEPRZETWARZANIESYGNALOW_SINUSOIDALSIGNAL_H


#include <vector>
#include "Signal.h"

class SinusoidalSignal : public Signal {
private:
    std::vector<double> data;
    double amplitude;
    double term;
    double startTime;
    double duration;
public:
    SinusoidalSignal(double amplitude, double term, double startTime, double duration);
    ~SinusoidalSignal() override = default;

    void generate() override;
    void display() const override;
};

#endif //CYFROWEPRZETWARZANIESYGNALOW_SINUSOIDALSIGNAL_H
